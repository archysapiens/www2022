<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '1024M');
ini_set('max_execution_time', 12000);
require('../general/generales.inc');
//require('../ptma_opcd/pfma_validacion_archivos.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');

$IndMando = array("01","08","10","30","50","60","70","75","80","90");


$GestorArchivo = fopen("reporte_contratos.txt", "w");
if (!$GestorArchivo) 
{
	echo "Error al abrir archivo Error |reporte_contratos.txt" ."|";
}

/**
$sql = "select distinct rfc
		from BDART742013
		where qnaproc >= '16' and 
		tipnom='11' and 
		financiamiento not in (5,6,7,11,13) and
		funcion !=10 and ur='CON'";
**/

$sql = "SELECT estado, RFC ,ur, curp, nombre, anioproc,qnaproc
		FROM EMPL_ART_74";		

$res = $db->execFetchAll($sql, "pro_nomina");
$Contador=0;
foreach ($res as $row) {
		$Edo =$row['ESTADO'];
		$RFC =$row['RFC'];
		$UR =$row['UR'];
		$CURP =$row['CURP'];
		echo "$RFC|$Edo|$UR|CURP \n";

/**
		$dbDet = new DbOracle("pro_nomina", "ArchiSoft");	

		$sqlART="select rfc, UR
				from RFC_ART_74_CMPLTO
				where rfc = '$RFC' ";

       	$resDet = $dbDet->execFetchAll($sqlART, "Query Example");
		$URS    = "";

        foreach ($resDet as $rowDet) {
						$Rfc = $rowDet['RFC'];
						$UR  = $rowDet['UR'];
						$URS.= $UR . "|";
		} //fin del if de apertuta archivo
		//echo $RFC . "|".$URS . "\n";

		fwrite($GestorArchivo,$RFC . "|".$URS . "\n");
		$Contador++;
**/		
} // fin del for reach

echo "totasl de registros >>".$Contador."< <br>";
fclose($GestorArchivo);

?>		        