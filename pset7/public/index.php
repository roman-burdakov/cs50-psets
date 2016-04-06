<?php

    // configuration
    require("../includes/config.php"); 

    // get user data
    $users = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    // return format is an array. we expecting only one user since id uniqeness 
    // is enforced by db constraint for primary key.
    $user = $users[0];
    // load user portfolio
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", 
        $_SESSION["id"]);
    $positions = [];
    foreach ($rows as $row)
    {
        // load current stock position
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $total = $row["shares"] * $stock["price"];
            $positions[] = [
                "name" => $stock["name"],
                "price" => number_format($stock["price"], 2, ',', ' '),
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => number_format($total, 2, ',', ' ')
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio",
        "cash" => $user["cash"]]);
   

?>
