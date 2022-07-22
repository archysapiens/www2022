<?php
//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '8024M');
ini_set('max_execution_time', 240000);
require('../../general/generales.inc');
require('ac_db_pn.php');
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');

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
$PunteroAnio=CERO;
$PosicionArrayQnas=CERO;
$AuxUR ="";

$GestorArchivo = fopen("reporte_debug.dsv", "r");


if (!$GestorArchivo ) {
	echo "Error al abrir archivo Error |reporte_debug.dsv";
}
else{
	$Contador=0;
	$AntEdo="";
	$ActEdo="XXXX";
	$ESTADO = "";
	$UR  = "";
	$CURP  = "";
	$NOMBRE  = "";
	$QNAPROC  = "";
	$ANIOPROC  = "";

	while (($Registro = fgets($GestorArchivo, 4096)) !== false)  {
		$AuxRegistro =  $Registro;

		$ArrRegistro = explode("|",$AuxRegistro);
		$AuxRfc=$ArrRegistro[CERO];
		$RFC = preg_replace('/[^A-Za-z0-9\-]/', '', $AuxRfc);
		$ESTADO = $ArrRegistro[UNO];
		$UR  = $ArrRegistro[DOS];
		$CURP  = $ArrRegistro[TRES];
		$NOMBRE  = $ArrRegistro[CUATRO];
		$QNAPROC  = (int)$ArrRegistro[CINCO];
		$ANIOPROC  = (int)$ArrRegistro[SEIS];

		$AntEdo=$ActEdo;	
		$ActEdo=$ESTADO.$RFC;
		switch ($ANIOPROC) {
		    case 2013:
		        $PunteroAnio=0;		        break;
		    case 2014:
		        $PunteroAnio=24;		    break;
		    case 2015:
		        $PunteroAnio=48;		    break;
		    case 2016:
		        $PunteroAnio=72;		    break;
		}

		if($AntEdo != $ActEdo){
			if($Key!=CERO){
					foreach ($ArrContratos as $KKey => $value ) {
							$StrOut= $KKey."|";
							foreach($value as $data => $user_data)    
					            $StrOut .= $user_data."|";
					}	
					echo $StrOut."\n";
			}

			$Key=$ANIOPROC."/".$QNAPROC."|".$ESTADO."|".$RFC."|".$CURP."|".$NOMBRE;
			for($IndQna=16;$IndQna < 100; $IndQna++)
				$ArrContratos[$Key][$IndQna] = "-";
		}// fin if	

		$PosicionArrayQnas = $QNAPROC + $PunteroAnio;
		$AuxUR = $ArrContratos[$Key][$PosicionArrayQnas];
		if($AuxUR == "-")
			$ArrContratos[$Key][$PosicionArrayQnas] = $UR;
		else
			$ArrContratos[$Key][$PosicionArrayQnas] = $AuxUR."-".$UR;
	} //fin del while
	$Contador++;
}// fin del if
fclose($GestorArchivo);

?>		        