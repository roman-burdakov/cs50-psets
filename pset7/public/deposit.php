<?php
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // amount symbol is required
        if (empty($_POST["amount"]) || !is_numeric($_POST["amount"]) 
            || $_POST["amount"] <= 0)
        {
            apologize("You need to set amount of cash for deposit.");
        }
        if ($_POST["amount"] > 10000) {
            apologize("Maximum of \$10,000 is allowed for deposit.");
        }

        $result = CS50::query("UPDATE users set cash = cash + ? 
            WHERE id = ?", $_POST["amount"], $_SESSION["id"]);
        if (!$result) {
            // should never be here, but if are, return error
            apologize("We appologize, but your deposit can not be completed.");
        }
        
        // log deposit activity
        CS50::query("INSERT INTO history (user_id, transaction_type, symbol,
            amount, price_per_share) VALUES(?, ?, ?, ?, ?)", 
            $_SESSION["id"], "DEPOSIT", "\$\$\$", 0, $_POST["amount"]);
        // send user to home
        redirect("/"); 
    } 
    else
    {
        // else render deposit form
        render("deposit_form.php", ["title" => "Make a deposit"]);
    }
?>