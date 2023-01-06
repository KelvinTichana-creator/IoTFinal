<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "IoTFinalProject";

$con = mysqli_connect($servername,$username,$password,$dbname);


$temperature = isset($_GET['temp']) ? $_GET['temp'] : '';
$LDR = isset($_GET['Light']) ? $_GET['Light'] : '';


$sql = "INSERT INTO Sensors (Temperature,LightIntensity) VALUES('$temperature','$LDR')";

if(mysqli_query($con,$sql))
    echo "New record created successfully";

?>