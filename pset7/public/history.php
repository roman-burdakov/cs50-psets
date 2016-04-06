<?php
    // configuration
    require("../includes/config.php");
    
    // load history
    $records = CS50::query("SELECT * FROM history WHERE user_id = ?", 
        $_SESSION["id"]);
      
    // render transactions view
    render("transactions.php", ["title" => "History", "positions" => $records]);
?>