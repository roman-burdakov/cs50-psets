<?php
    // configuration
    require("../includes/config.php");
    
    // on form submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate payload - symbol and amount
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        if (empty($_POST["amount"]) || !is_numeric($_POST["amount"]))
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
        
        // get user's buying power
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", 
            $_SESSION["id"]);
        $cash = $rows[0]["cash"];
        // find out how much would it cost to resolve transaction
        $cost = $stock["price"] * $_POST["amount"];
        
        // check if user can afford that transaction
        if ($cost <= $cash)
        {
            // update cash
            CS50::query("UPDATE users set cash = cash - ? WHERE id = ?", $cost, 
                $_SESSION["id"]);
            // update portfolio
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) 
                VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + 
                VALUES(shares)", $_SESSION["id"], $stock["symbol"], 
                $_POST["amount"]);
            // log transaction data
            CS50::query("INSERT INTO history (user_id, transaction_type, symbol,
                amount, price_per_share) VALUES(?, ?, ?, ?, ?)", 
                $_SESSION["id"], "BUY", $stock["symbol"], $_POST["amount"], 
                $cost);
            // send user to home
            redirect("/"); 
        }        
        else
        {
            apologize("You can't afford that.");
        }
    }
    
    else
    {
        // GET request to render form
        render("buy_form.php", ["title" => "Buy"]);
    }
?>