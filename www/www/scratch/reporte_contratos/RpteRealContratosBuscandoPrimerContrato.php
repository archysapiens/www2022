<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//

// RpteRealContratosV4_AutoPivotV2
// Busca liberar memoria

ini_set('memory_limit', '8024M');
ini_set('max_execution_time', 240000);
require('../../../general/generales.inc');
//require('ac_db_pn.php');

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);


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
$PosicionArrayQnas=50;
$ArchivoEntrada =$argv[UNO];
$ArrPosQnas = array(0,24,48,72);
$AnioIni="";
$QnaIni="";
$FecInicioContrato ="";	
$GestorArchivo = fopen($ArchivoEntrada, "r");


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
		$QNAPROCAUX  = $ArrRegistro[CINCO];
		$QNAPROC  = (int)$ArrRegistro[CINCO];
		$ANIOPROC  = (int)$ArrRegistro[SEIS];

		$AntEdo=$ActEdo;	
		$ActEdo=$ESTADO.$RFC;

		switch ($ANIOPROC) {
		    case 2013:
		        $PunteroAnio =  0; break;
		    case 2014:
		        $PunteroAnio = 24; break;
		    case 2015:
		        $PunteroAnio = 48; break;
		    case 2016:
		        $PunteroAnio = 72; break;
		}// sqitch

		if($AntEdo != $ActEdo){
			if($Key!=CERO) {
				    $BanIniCon = "";
					foreach ($ArrContratos as $KKey => $value ) {
							$StrOut= $KKey."|";
							$ContadorQuincenas = 16;
							foreach($value as $data => $user_data) {
					            $StrOut .= $user_data."|";
					            $IniCon  = $user_data;
					            if ($BanIniCon == "" and $IniCon == "CON"){
					            	if ($ContadorQuincenas <=24){
					            		$AnioIni="2013";	
					            		$QnaIni = str_pad($ContadorQuincenas,2,"0",STR_PAD_LEFT);	
					            	}
					            	if ($ContadorQuincenas > 24 and $ContadorQuincenas <=48){
					            		$AnioIni="2014";	
					            		$QnaIni = str_pad(($ContadorQuincenas)-24,2,"0",STR_PAD_LEFT);	
					            	}
					            	if ($ContadorQuincenas > 48 and $ContadorQuincenas <=72){
					            		$AnioIni="2015";	
					            		$QnaIni = str_pad(($ContadorQuincenas)-48,2,"0",STR_PAD_LEFT);	
					            	}
					            	if ($ContadorQuincenas > 72 and $ContadorQuincenas <=97){
					            		$AnioIni="2016";	
					            		$QnaIni = str_pad(($ContadorQuincenas)-72,2,"0",STR_PAD_LEFT);	
					            	}

					            	$FecInicioContrato = "$AnioIni/$QnaIni";
					            	$BanIniCon = "Completado";
					            }
					            $ContadorQuincenas++;
					        }       
					}	
					echo $StrOut."$FecInicioContrato|\n";
					for($IndQna = 16; $IndQna < 97; $IndQna++)
						unset($ArrContratos[$Key][$IndQna]);
			}

			$Key=$ANIOPROC."/".$QNAPROCAUX."|".$ESTADO."|".$RFC."|".$CURP."|".$NOMBRE;
			for($IndQna=16;$IndQna < 97; $IndQna++)
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

foreach ($ArrContratos as $KKey => $value ) {
		$StrOut= $KKey."|";
		$ContadorQuincenas = 16;
		foreach($value as $data => $user_data) {
            $StrOut .= $user_data."|";
            $IniCon  = $user_data;
            if ($BanIniCon == "" and $IniCon == "CON"){
            	if ($ContadorQuincenas <=24){
            		$AnioIni="2013";	
            		$QnaIni = str_pad($ContadorQuincenas,2,"0",STR_PAD_LEFT);	
            	}
            	if ($ContadorQuincenas > 24 and $ContadorQuincenas <=48){
            		$AnioIni="2014";	
            		$QnaIni = str_pad(($ContadorQuincenas)-24,2,"0",STR_PAD_LEFT);	
            	}
            	if ($ContadorQuincenas > 48 and $ContadorQuincenas <=72){
            		$AnioIni="2015";	
            		$QnaIni = str_pad(($ContadorQuincenas)-48,2,"0",STR_PAD_LEFT);	
            	}
            	if ($ContadorQuincenas > 72 and $ContadorQuincenas <=97){
            		$AnioIni="2016";	
            		$QnaIni = str_pad(($ContadorQuincenas)-72,2,"0",STR_PAD_LEFT);	
            	}

            	$FecInicioContrato = "$AnioIni/$QnaIni";
            	$BanIniCon = "Completado";
            }
            $ContadorQuincenas++;
        }       
}	
echo $StrOut."$FecInicioContrato|\n";
for($IndQna = 16; $IndQna < 97; $IndQna++)
	unset($ArrContratos[$Key][$IndQna]);



?>		        