<?php
ini_set('display_errors', 1);
session_start();

include "../general/DBC.php";
include "../general/generales.inc";
include "ptfma_cruda_archivo.inc";
include "ptfma_producto.inc";
include "pfma_validacion_archivos.inc";
include "pfma_validacion_archivos_trailer.inc";
date_default_timezone_set('America/Mexico_City');

//$_POST = $_SESSION ;

$TagEnvio="";
if(isset($_POST['TagEnvio']))
	$TagEnvio=$_POST['TagEnvio'];

$IdRemesa="";
if(isset($_POST['idremesa']))
	$IdRemesa=$_POST['idremesa'];

$IdArchivoPN="";
if(isset($_POST['idarchivopn']))
	$IdArchivoPN=$_POST['idarchivopn'];

$IdArchivoPN=$TagEnvio."_".$IdArchivoPN;

$Operacion="";
if(isset($_POST['operacion']))
	$Operacion=$_POST['operacion'];

$ProductoNomina="";
if(isset($_POST['pn']))
	$ProductoNomina=$_POST['pn'];

$AnioEnvio="";
if(isset($_POST['anio_envio']))
	$AnioEnvio=$_POST['anio_envio'];

$QnaEnvio="";
if(isset($_POST['quincena_envio']))
	$QnaEnvio=$_POST['quincena_envio'];

/**
	echo "TagEnvio >>$TagEnvio<<            <br>";
	echo "IdRemesa >$IdRemesa<              <br>";
	echo "IdArchivoPN >>$IdArchivoPN<       <br>";
	echo "Operacion >>$Operacion<           <br>";
	echo "ProductoNomina >>$ProductoNomina< <br>";
**/


$ArrTagEnvio= explode("-", $TagEnvio);
$IdOrg = $ArrTagEnvio[CERO];
$AnioProc = $ArrTagEnvio[UNO];
$QnaProc = $ArrTagEnvio[DOS];

///// DEFINICION DE CATALOGOS

// sE UTILIZA EN REGLA fncValidaDI_3
$CatEdo = array("AS" , "BC","BS", "CC", "CL", "CM","CS", "CH", "DF", 
				"DG", "GT", "GR", "HG", "JC", "MC","MN", "MS", "NT", "NL", "OC",
				"PL", "QT", "QR", "SP","SL", "SR", "TC", "TS", "TL","VZ", "YN", "ZS", "NE");

// sE UTILIZA EN REGLA fncValidaDI_7
	$TESOFE = array("2001","37006","37009","37019","37135","37166","37168","40002","40012",
"40014","40021","40022","40030","40032","40036","40037","40042","40044","40058","40059","40060",
"40062","40072","40102","40103","40106","40108","40110","40112","40113","40116","40124","40126",
"40127","40128","40129","40130","40131","40132","40133","40134","40136","40137","40138","40139",
"40140","40143","90600");

$UR= explode("\n", file_get_contents('../mto/cat_ur.txt'));

// sE UTILIZA EN REGLA fncValidaDI_23
$Pto= explode("\n", file_get_contents('../mto/cat_puestos.txt'));	

// sE UTILIZA EN REGLA fncValidaDI_25
$Edo= explode("\n", file_get_contents('../mto/cat_estados.txt'));

// sE UTILIZA EN REGLA fncValidaDI_26
$Mpio= explode("\n", file_get_contents('../mto/mpio_'.$IdOrg.'.txt'));

// 1 DIRECTIVA DE CALIDAD PARA ESTRUCTURA PROGRAMÁTICA

$EPO = explode("\n", file_get_contents('../mto/cat_ep_otros.txt'));
$EPC = explode("\n", file_get_contents('../mto/cat_ep_camcelados.txt'));
$UREP=array("X00","416","610","DF","HO");
$URA74=array("CON", "REG", "HOM", "FOR","FO2", "FO3", "EST" , "416");


// 4 DIRECTIVA DE CALIDAD AÑO REAL
$Periodo = explode("\n", file_get_contents('../mto/cat_periodo.txt'));


//   7.	DIRECTIVA DE CALIDAD TIPOS NOMINA Y CONCEPTOS

$NominaConcepto = explode("\n", file_get_contents('../mto/cat_nomina_concepto.txt'));

// 8.	DIRECTIVA DE CALIDAD CLUES
$CLUES = explode("\n", file_get_contents('../mto/cat_clues_'.$IdOrg.'.txt'));


// 10.	DIRECTIVA DE CALIDAD UR-CATALOGO DE CONCEPTOS
$UR_610 = explode("\n", file_get_contents('../mto/cat_ur_cptos_610.txt');
$UR_DF  = explode("\n", file_get_contents('../mto/cat_ur_cptos_DF.txt');
$UR_HO  = explode("\n", file_get_contents('../mto/cat_ur_cptos_HO.txt');
$UR_X00 = explode("\n", file_get_contents('cat_ur_cptos_X00.txt');


//print_r($Mpio);

if($Operacion=="eliminar"){
	$Resultado = eliminaArchivoPN($IdArchivoPN, $TagEnvio,$IdRemesa);
	if($Resultado== CERO){
		$TablaArchivoProdNomina = obtenArchivoPN($AnioProc, $QnaProc,$IdOrg);
        echo $TablaArchivoProdNomina;
	}
	else
		echo "<br><br> ERROR al eliminar Archivo <br><br>";
}
else if($Operacion=="analizar"){

	$ResultadoValidacionDat = fncValidaArchivo($IdOrg, "../staging/",$IdArchivoPN.".dat");
	$ResultadoRegistro = registraResultadoValidacion($TagEnvio,$IdArchivoPN.".dat",$ResultadoValidacionDat,$ProductoNomina);	

	// en esta funcion se usan solo dos parametros

	$ResultadoValidacionTra = fncValidaArchivoTrailer($IdOrg,"../staging/".$IdArchivoPN.".tra");

	$ResultadoRegistro = registraResultadoValidacion($TagEnvio,$IdArchivoPN.".tra",$ResultadoValidacionTra,$ProductoNomina);

	if($ResultadoValidacionDat > CERO){
		// "D" Archivo de Datos
		$Resultado = cargaRegistrosError($IdRemesa, $TagEnvio,$IdArchivoPN,"D");
	}
	if($ResultadoValidacionTra > CERO){
		// "T" Archivo Trail
		$Resultado = cargaRegistrosError($IdRemesa, $TagEnvio,$IdArchivoPN,"T");
	}

	$TablaArchivoProdNomina = obtenArchivoPN($AnioProc, $QnaProc,$IdOrg);
    echo $TablaArchivoProdNomina;
}
else
	echo "<br><br>No se identifica la operacion <br><br>";
	
?>