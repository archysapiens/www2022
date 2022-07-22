<?php
//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '8024M');
ini_set('max_execution_time', 240000);
require('../../general/generales.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');
$ArchivoEntrada =$argv[UNO];
$GestorArchivo = fopen($ArchivoEntrada, "r");

if (!$GestorArchivo) {
	echo "Error al abrir archivo Error |ArchivoEntrada";
}
else{
	while (($Registro = fgets($GestorArchivo, 4096)) !== false)  {
		$RFC = preg_replace('/[^A-Za-z0-9\-]/', '', $Registro);
		//echo "RFC >>".$RFC . "<<\n";
		$Contador=0;
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
						if($AntEdo != $ActEdo){
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
						
		} //fin del if de apertuta archivo
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

?>		        