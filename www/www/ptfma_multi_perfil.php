<?php
session_start();
include "ptma_opcd/ptfma_multi_perfil.inc";


$Perfiles="";
if(isset($_SESSION['perfiles']))
	$Perfiles = $_SESSION['perfiles'];

//echo "Perfiles >$Perfiles< <br>";

$ArrPerfiles = explode("|", $Perfiles);

//print_r($ArrPerfiles);

echo fncBuildHead();
echo fncBuildBody($ArrPerfiles);
echo fncBuildJS();
	

?>

