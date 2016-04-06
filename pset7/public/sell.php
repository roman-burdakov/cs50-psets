<?php
    // configuration
    require("../includes/config.php"); 
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate payload - symbol and amount
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        if (empty($_POST["amount"]) || !is_numeric($_POST["amount"]) 
            || $_POST["amount"] <= 0)
        {
            apologize("Please enter valid amount.");
        }
        
        // get latest stock price
        $stock = lookup($_POST["symbol"]);
        // check if real stock symbol
        if ($stock === false)
        {
            apologize("Symbol not found.");
        }
        // find and check if user has corresponding position in his portfolio
        $position = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? 
            and symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        if ($position === false)
        {
           apologize("Error while selling shares.");
        }
        if ($position[0]["shares"] < $_POST["amount"])
        {
           apologize("You don't own corresponding amount of stocks.");
        }
        // check that user has enough buying power
        // NB. We expect having position for give user and symbol to be unique.
        // that is enforced through db constraint.
        $value = $stock["price"] * $_POST["amount"];
        // update users with cash
        CS50::query("UPDATE users set cash = cash + ? WHERE id = ?", $value, 
            $_SESSION["id"]);
        // update portfolio
        if ($_POST["amount"] == $position[0]["shares"]) 
        {
            CS50::query("DELETE from portfolios where user_id =? and symbol =?", 
            $_SESSION["id"], $_POST["symbol"]); 
        }
        else 
        {
            CS50::query("UPDATE portfolios set shares = ? where user_id = ? 
                and symbol = ?", $position[0]["shares"] - $_POST["amount"], 
                $_SESSION["id"], $_POST["symbol"]); 
        }
        // log transaction
        CS50::query("INSERT INTO history (user_id, transaction_type, symbol, 
            amount, price_per_share) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], 
            "SELL", $stock["symbol"], $_POST["amount"], $value);    
        // redirect to home page
        redirect("/");
    }
    else
    {
        $position = CS50::query("SELECT * FROM portfolios WHERE user_id = ?",
            $_SESSION["id"]);
        if ($position === false)
        {
           apologize("Nothing to sell.");
        }
        // render sell form
        render("sell_form.php", ["title" => "Sell", "positions" => $position]);
    }
?>
