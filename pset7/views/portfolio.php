<div id="middle">
    <table class="table table-striped">
    
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
    
        <tbody>
        <?php
            foreach ($positions as $position)
            {
                print("<tr>");
                print("<td>{$position["symbol"]}</td>");
                print("<td>{$position["name"]}</td>");
                print("<td>{$position["shares"]}</td>");
                print("<td>\${$position["price"]}</td>");
                print("<td>\${$position["total"]}</td>");
                print("</tr>");
            }
    
        ?>
        <tr>
            <td colspan="4">CASH</td>
            <td>$<?= number_format($cash, 2, ',', ' ') ?></td>
        </tr>
        </tbody>
    </table>
</div>
