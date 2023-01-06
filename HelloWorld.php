<?php

//$servername = "localhost";
//$username = "root";
//$password = "";
//$dbname = "IoTFinalProject";
/*
$con = mysqli_connect("localhost","root","","IoTFinalProject");           
echo $LightIntensity = isset($_GET['LightIntensity']) ? $_GET['LightIntensity'] : ''. "<br/>";
echo $Temperature = isset($_GET['Temperature']) ? $_GET['Tempereture'] : ''. "<br/>"; 
$sql = "INSERT INTO Sensors (LightIntensity, Temperature) VALUES ('{$LightIntensity}','{$Temperature}')";     

if (mysqli_query($con, $sql)) {
    echo "New record created successfully";
} else {
    echo "Unsuccessful";
}
*/
$servername = "localhost";
$database = "IoTFinalProject";
$username = "root";
$password = "";


// Create connection
$conn = mysqli_connect($servername, $username, $password, $database);
// Check connection
if (!$conn) {
      die("Connection failed: " . mysqli_connect_error());
}
 
echo "Connected successfully";
 $LightIntensity = isset($_GET['LightIntensity']) ? $_GET['LightIntensity'] : '';
 $Temperature = isset($_GET['Temperature']) ? $_GET['Temperature'] : '';
 
$sql = "INSERT INTO Sensors (LightIntensity,Temperature) VALUES ('{$LightIntensity}', '{$Temperature}')";
if (mysqli_query($conn, $sql)) {
      echo "New record created successfully";
} else {
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}
mysqli_close($conn);
?>

