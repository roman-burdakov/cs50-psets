<?php
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // stock symbol is required
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        
        // get stock price, full name, etc.
        $stock = lookup($_POST["symbol"]);
        
        if ($stock === false)
        {
            apologize("Symbol not found.");
        } 
        else 
        {
            // render result stock view
            render("quote_display.php", ["title" => $stock["name"]." quote", 
                "price" => number_format($stock["price"], 2, ',', ' '), 
                "name" => $stock["name"], "symbol" => $stock["symbol"]]);
        }
    } 
    else
    {
        // else render quote request form
        render("quote_form.php", ["title" => "Quote"]);
    }
?>
