<?php
//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '4024M');
ini_set('max_execution_time', 12000);
require('../../general/generales.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');
$ArchivoEntrada =$argv[UNO];
$ArchivoDetalle =$argv[DOS];
$GestorArchivo = fopen($ArchivoEntrada, "r");
$GestorArchivoDet = fopen($ArchivoDetalle, "r");

if (!$GestorArchivo or !$GestorArchivoDet) {
	echo "Error al abrir archivo Error |ArchivoEntrada";
}
else{
	while (($Registro = fgets($GestorArchivo, 4096)) !== false)  {
		$RFC = preg_replace('/[^A-Za-z0-9\-]/', '', $Registro);
		//echo "RFC >>".$RFC . "<<\n";
		$Contador=0;
		$AntEdo="";
		$ActEdo="XXXX";
		$ESTADO = "";
		$UR  = "";
		$CURP  = "";
		$NOMBRE  = "";
		$QNAPROC  = "";
		$ANIOPROC  = "";



		while (($RegistroDet = fgets($GestorArchivoDet, 4096)) !== false)  {
			$ArrRegistroDet = explode("|",$RegistroDet);
			$RFCDet = $ArrRegistroDet[CERO];

			$ESTADO = $rowDet[UNO];
			$UR  = $rowDet[DOS];
			$CURP  = $rowDet[TRES];
			$NOMBRE  = $rowDet[CUATRO];
			$QNAPROC  = (int)$rowDet[CINCO];
			$ANIOPROC  = (int)$rowDet[SEIS];

			if($RFC == $RFCDet){
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

				if($AntEdo != $ActEdo){
					$Key=$ESTADO."-".$RFC;
					for($IndQna=16;$IndQna < 97; $IndQna++)
						$ArrContratos[$Key][$IndQna] = "-";
				}// fin if	
				$PosicionArrayQnas = $QNAPROC + $PunteroAnio;
				$AuxUR = $ArrContratos[$Key][$PosicionArrayQnas];
				if($AuxUR == "-")
					$ArrContratos[$Key][$PosicionArrayQnas] = $UR;
				else
					$ArrContratos[$Key][$PosicionArrayQnas] = $AuxUR."-".$UR;
			} 
			else{
				fseek($GestorArchivoDet, -4096, SEEK_CUR);
				break;
			}// fin del if($RFC == $RFCDet){
		}// fin del while	

		foreach ($ArrContratos as $KKey => $value ) {
				$StrOut= $KKey."|";
				foreach($value as $data => $user_data)    {
		            $StrOut .= $user_data."|";
		        }
		}	
		echo $StrOut."\n";
	$Contador++;
	} // fin del while
}// fin del if
fclose($GestorArchivo);
fclose($GestorArchivoDet);
?>		        