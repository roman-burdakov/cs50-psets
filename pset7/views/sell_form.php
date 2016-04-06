<div id="middle">
    <form action="sell.php" method="post">
        <fieldset>
            <div class="form-group">
                <select class="form-control" name="symbol">
                <?php
                    foreach ($positions as $position)
                    {
                        print("<option value=\"{$position["symbol"]}\">
                        {$position["symbol"]}</option>");
                    }
                ?>
                </select>
            </div>
            <div class="form-group">
                <input autocomplete="off" class="form-control" name="amount" placeholder="Amount" type="text">
            </div>
            <div class="form-group">
                <button class="btn btn-default" type="submit">Sell</button>
            </div>
        </fieldset>
    </form>
</div>