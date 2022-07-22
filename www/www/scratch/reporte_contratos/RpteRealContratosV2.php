<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '4024M');
ini_set('max_execution_time', 12000);
require('../../general/generales.inc');
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

$sql = "SELECT distinct RFC
		FROM reporte_etapa1";		

$res = $db->execFetchAll($sql, "pro_nomina");
$Contador=0;
foreach ($res as $row) {
		
		$RFC =$row['RFC'];
		//echo "RFC >>$RFC<< ";
		
		

		//$Linea= "$RFC|$Edo|$UR|$CURP \n";
		//fwrite($GestorArchivo,$Linea);


		$dbDet = new DbOracle("pro_nomina", "ArchiSoft");	

		$sqlART="select estado, ur,CURP,NOMBRE,qnaproc,anioproc
					from reporte_etapa1
					where rfc='$RFC'
					order by anioproc,rfc,estado,qnaproc";

       	$resDet = $dbDet->execFetchAll($sqlART, "Query Example");
		$URS    = "";
		$AntEdo="";
		$ActEdo="XXXX";
		$ESTADO = "";
		$UR  = "";
		$CURP  = "";
		$NOMBRE  = "";
		$QNAPROC  = "";
		$ANIOPROC  = "";
		$StrOut="";
		$Key=0;


        foreach ($resDet as $rowDet) {
						$ESTADO = $rowDet['ESTADO'];
						$UR  = $rowDet['UR'];
						$CURP  = $rowDet['CURP'];
						$NOMBRE  = $rowDet['NOMBRE'];
						$QNAPROC  = (int)$rowDet['QNAPROC'];
						$ANIOPROC  = (int)$rowDet['ANIOPROC'];

						$AntEdo=$ActEdo;	
						$ActEdo=$ESTADO;
						switch ($ANIOPROC) {
						    case 2013:
						        $PunteroAnio=0;
						        break;

						    case 2014:
						        $PunteroAnio=24;
						        break;
						    case 2015:
						        $PunteroAnio=48;
						        break;
						    case 2016:
						        $PunteroAnio=72;
						        break;
    
						}

					//	echo "AntEdo >>$AntEdo<< ActEdo *>>$ActEdo<< \n";

						if($AntEdo != $ActEdo){

							$Key=$ESTADO."-".$RFC;
					//		echo "Inicia Arregloe Key >>$Key<< \n";

							//$StrOut=$ANIOPROC."|".$ESTADO."|".$RFC."|";
							for($IndQna=16;$IndQna < 97; $IndQna++)
								$ArrContratos[$Key][$IndQna] = CERO;

					//		print_r($ArrContratos[$Key]);

						}// fin if	
						$PosicionArrayQnas = $QNAPROC + $PunteroAnio;
						$ArrContratos[$Key][$PosicionArrayQnas] = $UR;

						//$StrOut.=	$UR."|";
						
		} //fin del if de apertuta archivo
		//echo $RFC . "|".$URS . "\n";
		foreach ($ArrContratos as $KKey => $value ) {
				$StrOut= $KKey."|";
				foreach($value as $data => $user_data)    {
		            $StrOut .= $user_data."|";
		        }
		}	
		echo $StrOut."\n";

		//fwrite($GestorArchivo,$RFC . "|".$URS . "\n");

$Contador++;
//if($Contador > 200000000)
	//break;
} // fin del for reach

echo "totasl de registros >>".$Contador."< <br>";
//fclose($GestorArchivo);

?>		        