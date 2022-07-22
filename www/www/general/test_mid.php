<?php

include "../general/generales.inc";
include 'mid_oracle.inc';


$TagEnvio="123456789";
$SQL = "select ur, descripcion from ur";

$res=ejecutaSQLOracle($SQL, $TagEnvio);

print_r($res);

/**
foreach ($res as $row) {
				$SerPub =$row['SERPUB'];
				$UR=$row['UR'];
				$CveNiv =$row['NIVELPUESTO'];
}				
**/


?>