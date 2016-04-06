<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("Username is required for registration.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("Password is required for registration.");
        }
        else if (empty($_POST["confirmation"]) 
            || ($_POST["confirmation"] !== $_POST["password"]))
        {
            apologize("Your password confirmation doesn't match with entered 
                password.");
        }
        
        $result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) 
            VALUES(?, ?, 10000.0000)", $_POST["username"], 
            password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        if ($result === false)
        {
            apologize("Username is already taken.");    
        }
        else
        {
            // updade session with user id.
            $_SESSION["id"] = $row["id"];
            // redirect to home
            redirect("/");
        }
    }

?>