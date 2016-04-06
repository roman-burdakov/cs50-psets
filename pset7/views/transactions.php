<div id="middle">
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Transaction</th>
                <th>Date/Time</th>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price</th>
            </tr>
        </thead>
        <tbody>
        
        <?php
            foreach ($positions as $position)
            {
                $purchased = date('m/d/y g:i a',
                    strtotime($position["purchase_ts"]));
                $price = '$' . 
                    number_format($position["price_per_share"], 2, ',', ' ');
                print("<tr>");
                print("<td class='{$position["transaction_type"]}'>
                    {$position["transaction_type"]}</td>");
                print("<td>{$purchased}</td>");
                print("<td>{$position["symbol"]}</td>");
                print("<td>{$position["amount"]}</td>");
                print("<td>{$price}</td>");
                print("</tr>");
            }
        ?>
        </tbody>
    </table>
</div>