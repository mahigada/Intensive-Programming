<?php
$mysqli = new mysqli("127.0.0.1", "root", "rootpassword", "stocks");
$order_by = $_GET["order_by"];
$sorting = $_GET["sorting"];
if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: " . $mysqli->connect_error;
    exit();
  }
$table_name = "`yahoo_2020_12_07_Dec_59_1607371161.html`";
$sql = "SELECT * FROM $table_name";
if ($order_by && $sorting) {
    $sql = "SELECT * FROM $table_name ORDER BY $order_by $sorting";
}
$result = $mysqli->query($sql);
$mysqli->close();
?>
<h1>

    <?php echo "Stocks Table<br>yahoo_2020_12_07_Dec_59_1607371161"?>
    
     
</h1>
<table>
    <thead>
        <th><a href="?order_by=symbol&sorting=<?php if ($order_by == "Symbol" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }?>">Symbol</a></th>
        <th><a href="?order_by=name&sorting=<?php if ($order_by == "Name" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }?>">Name</a></th>
        <th><a href="?order_by=price&sorting=<?php if ($order_by == "Price" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">Price</a></th>
        <th><a href="?order_by=chng&sorting=<?php if ($order_by == "Chng" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">Change</a></th>
        <th><a href="?order_by=percentChange&sorting=<?php if ($order_by == "percentChange" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">Percent Change</a></th>
        <th><a href="?order_by=volume&sorting=<?php if ($order_by == "Volume" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">Volume</a></th>
        <th><a href="?order_by=avgVolume&sorting=<?php if ($order_by == "avgVolume" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">Average Volume</a></th>
        <th><a href="?order_by=marketCap&sorting=<?php if ($order_by == "marketCap" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">Market Cap</a></th>
        <th><a href="?order_by=peRatio&sorting=<?php if ($order_by == "peRatio" && $sorting != "desc") { echo "desc"; } else { echo "asc"; }  ?>">PE Ratio</a></th>
    </thead>
    <tbody>
        <?php
            if ($result->num_rows > 0) {
                while($row = $result->fetch_assoc()) {
                    echo "<tr><td>" . $row["Symbol"]. "</td> <td>" . $row["Name"]. "</td> <td>" . $row["Price"] . "</td> <td>" . $row["Chng"] . "</td> <td>" . $row["percentChange"] . "</td> <td>" . $row["Volume"] ."</td><td>". $row["avgVolume"] . "</td><td>" . $row["marketCap"]. "</td> <td>" . $row["peRatio"] . "</td></tr>";
                }
            } else {
                echo "0 results";
            }
        ?>
    </tbody>
</table>
<style>
    table, tr, td, th {
        
        border: 0.5px solid red;
    }
    table{margin-left: auto;
    margin-right: auto;}
    h1{text-align: center}
    
</style>