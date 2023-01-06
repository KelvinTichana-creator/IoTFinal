

<?php

// Connect to the database
$host = 'localhost';
$user = 'root';
$password = '';
$dbname = 'IoTFinalProject';

$conn = new mysqli($host, $user, $password, $dbname);

if ($conn->connect_error) {
  die('Connection failed: ' . $conn->connect_error);
}

// Fetch 10 rows from the table
$sql = 'SELECT * FROM Sensors LIMIT 10';
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // Output the data for each row
  while($row = $result->fetch_assoc()) {
    //echo  "Light Intensity    Temperature"; '<br>'
    echo $row['LightIntensity'] . ' ' . $row['Temperature'] . '<br>';
  }
} else {
  echo 'No results found';
}

$conn->close();
?>
