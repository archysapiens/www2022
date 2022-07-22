<?php
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//

// Genera_XVII_V2
// Se agrega la funcionalidad para que se cree el archivo excel
// Se inserta la ifnromacion en las seldas correspondientes
// Fecha: 03 de Nov del 2016
//

ini_set('memory_limit', '4024M');
ini_set('max_execution_time', 12000);
require('generales.inc');
require('ac_db_pn.php');
//require_once 'Classes/PHPExcel.php';
include 'Classes/PHPExcel/IOFactory.php';
require('Genera_XVII.inc');

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);

$fileType = 'Excel5';
$fileName = 'Formatocurricular.xls';

$fileNameW = 'Formatocurricular_03-nov.xls';

// Read the file
$objReader = PHPExcel_IOFactory::createReader($fileType);
$objPHPExcel = $objReader->load($fileName);

$ArchivoEntrada = $argv[UNO];
$Tabla10494=$ArchivoEntrada.".tbl";


//$objPHPExcel->getActiveSheet()->setTitle('hidden1');  
/**
		$objPHPExcel->addNamedRange( 
		        new PHPExcel_NamedRange(
		            'nivel',
		            $objPHPExcel->getSheetByName('hidden1'), 
		            'A1:A9'
		        ) 
		    );    

**/
/**
$objPHPExcel = new PHPExcel();
$objPHPExcel->getProperties()->setCreator("Secretaria de Salud")
               ->setLastModifiedBy("Dirección de Automatización de Procesos y Soporte Técnico")
               ->setTitle("Sistema Nacional de Transparencia")
               ->setSubject("Sistema Integrador / Vacantes")
               ->setDescription("Plazas Vacantes del Personal de base y Confianza ")
               ->setKeywords("Dirección General de Recursos Humanos")
               ->setCategory("Archivo de Carga Masiva");

		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();

		PHPExcel_Cell::setValueBinder( new PHPExcel_Cell_AdvancedValueBinder() );


		$objPHPExcel->setActiveSheetIndex(0)
					->setCellValueExplicit('A1', '22524',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValue('A2', 'TITULO')
					->setCellValue('B2', 'TITULO')					
					->setCellValue('C2', 'DESCRIPCION')					
					->setCellValue('A3', 'Información curricular de los(as) servidores(as) públicas(os)')
					->setCellValue('B3', 'LGTA70FXVII')					
					->setCellValue('C3', 'La información que los sujetos obligados deberán publicar en cumplimiento a la presente fracción es la curricular no confidencial relacionada con todos los(as) servidores(as) públicos(as) y/o personas que desempeñen un empleo, cargo o comisión y/o ejerzan actos de autoridad en el sujeto obligado ¿desde nivel de jefe de departamento o equivalente y hasta el titular del sujeto obligado¿, que permita conocer su trayectoria en el ámbito laboral y escolar.')					

		            ->setCellValueExplicit('A4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('B4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('C4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('E4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('F4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('G4', '1',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('H4', '9',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('I4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('J4', '10',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('K4', '7',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('L4', '9',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('M4', '4',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('N4', '1',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('O4', '12',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('P4', '13',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('Q4', '14',PHPExcel_Cell_DataType::TYPE_STRING)

		            ->setCellValueExplicit('A5', '10486',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('B5', '10482',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('C5', '10487',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D5', '10488',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('E5', '10489',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('F5', '10490',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('G5', '10491',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('H5', '10492',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('I5', '10495',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('J5', '10494',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('K5', '10493',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('L5', '10496',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('M5', '10480',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('N5', '10481',PHPExcel_Cell_DataType::TYPE_STRING)  
					->setCellValueExplicit('O5', '10484',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('P5', '10485',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('Q5', '10483',PHPExcel_Cell_DataType::TYPE_STRING)
	
		            ->setCellValue('A7', 'Clave o nivel del puesto')
		            ->setCellValue('B7', 'Denominación de puesto')
		            ->setCellValue('C7', 'Denominación del cargo')
		            ->setCellValue('D7', 'Nombre(s)')
		            ->setCellValue('E7', 'Primer Apellido ')
		            ->setCellValue('F7', 'Segundo Apellido ')
		            ->setCellValue('G7', 'Área o unidad administrativa de adscripción')  
					->setCellValue('H7', 'Nivel máximo de estudios')  
					->setCellValue('I7', 'Carrera Genérica')

		            ->setCellValue('J7', 'Experiencia laboral')
		            ->setCellValue('K7', 'Hipervínculo a versión pública del currículum')
		            ->setCellValue('L7', '¿Ha tenido sanciones administrativas?:')
		            ->setCellValue('M7', 'Fecha de validación')  
					->setCellValue('N7', 'Área responsable de la información')  
					->setCellValue('O7', 'Año')

		            ->setCellValue('P7', 'Fecha de actualización')
		            ->setCellValue('Q7', 'Nota');

		$objPHPExcel->getActiveSheet()->setTitle('Reporte de Formatos');

		$objPHPExcel->setActiveSheetIndex(UNO)
		            ->setCellValue('A1', 'Miembro del poder judicial')
		            ->setCellValue('A2', 'Representante popular')
		            ->setCellValue('A3', 'Prestador de servicios profesionales')
		            ->setCellValue('A4', 'Funcionario')
		            ->setCellValue('A5', 'Otro')
		            ->setCellValue('A6', 'Servidor público')
		            ->setCellValue('A7', 'Miembro de órgano autónomo')
		            ->setCellValue('A8', 'Empleado')
		            ->setCellValue('A9', 'Personal de confianza');
		            

**/


$GestorArchivo = fopen($ArchivoEntrada, "r");

$GestorArchivoTbl = fopen($Tabla10494, "w");

if (!$GestorArchivo ) {
	echo "Error al abrir archivo Error |ArchivoEntrada >>$ArchivoEntrada<< \n";
}
else{
	$FchVal="30/09/2016";
	$AreaResp="Direccion General de Recursos Humanos";
	$CVCTNIVEL="";
	$CVCTCARRERAESP="";
	$DescPuesto ="";
	$DenCargo ="";
	$AreaUniAds="";
	$CVCTNIVEL="";
	$CVCTCARRERAESP ="";
	$Nombre="";
	$AppPat="";
	$AppMat="";
	$AreaUniAds="";

	$ContadorRow=OCHO;
	$ContadorTab10494=CUATRO;

	while (($Registro = fgets($GestorArchivo, 4096)) !== false)  {
		$ArrRegistro = explode("\t",$Registro);
		$Id = $ArrRegistro[CERO];
		$Nombre = strtoupper ($ArrRegistro[4]);
		$AppPat = strtoupper ($ArrRegistro[5]);
		$AppMat = strtoupper ($ArrRegistro[6]);
		$CURP = strtoupper ($ArrRegistro[8]);
		$Puesto = strtoupper ($ArrRegistro[20]);
		$UR = strtoupper ($ArrRegistro[26]);

		echo "Id >$Id< Nombre >$Nombre< AppPat>$AppPat< AppMat >$AppMat< \n";

		$ExpLaboral="Pendiente Exp Lab";
		$Hipervinculo="";
		$SancionAdm="";

		$DescPuesto     = "";
		$DenCargo       = "";
		$AreaUniAds     = "";
		$CVCTNIVEL      = "";
		$CVCTCARRERAESP ="";
		$CVLABORAL_DEL          = "";
		$CVLABORAL_AL           = "";
		$CVLABORAL_EMPRESA      = "";
		$CVLABORAL_PUESTO       = "";
		$CVCTEXPERIECIA_CAMPO   = "";



		$db = new DbOracle("pro_nomina", "ArchiSoft");

/**

		$SQL = "select rv.curp, ev.nombre_unidad,ev.cve_unidad, ev.cve_puesto,
		rv.den_pto, CX.CTAREAS_DESCRIPCION,
		nvl((select cve_puesto from puestos_XVLL where nombre_puesto='$Puesto' and rownum=1),'Pendiente') cve_puesto,
		nvl((select desc_puesto from puestos_XVLL where nombre_puesto='$Puesto' and rownum=1),'Pendiente') desc_puesto,
		nvl(( select cvctnivel from(select cvctnivel from cvescolaridades_XVLL where cvdatospersonales_id='$Id'   order by cvescolaridad_del desc) a where rownum=1),'Pendiente') cvctnivel,
		nvl((select CVCTCARRERAESP from(select CVCTCARRERAESP from cvescolaridades_XVLL where cvdatospersonales_id='$Id' and CVCTCARRERAESP not like 'ESPECIALIDA%'   order by cvescolaridad_del desc)a where  rownum=1),'Pendiente') CVCTCARRERAESP,
		(select url from url_xvii where id = '$Id') url
		from rusp_xvii rv, empleados_xvll ev, CTAREAS_XVLL CX
		where rv.curp = ev.curp and  ev.curp = '$CURP' and  
		ev.nombre_unidad=CX.CTAREAS_PDFR";

**/

		$SQL = "SELECT rv.curp, rv.den_pto,
		nvl((select cve_puesto from puestos_XVLL where nombre_puesto='$Puesto' and rownum=1),'Pendiente') cve_puesto,
		nvl((select desc_puesto from puestos_XVLL where nombre_puesto='$Puesto' and rownum=1),'Pendiente') desc_puesto,
		nvl(( select cvctnivel from(select cvctnivel from cvescolaridades_XVLL where cvdatospersonales_id='$Id' and cvctnivel not like 'ESPECIALIDA%'   order by cvescolaridad_del desc) a where rownum=1),'ninguno') cvctnivel,
		nvl((select CVCTCARRERAESP from(select CVCTCARRERAESP from cvescolaridades_XVLL where cvdatospersonales_id='$Id'  and cvctnivel not like 'ESPECIALIDA%'  order by cvescolaridad_del desc)a where  rownum=1),'ninguno') CVCTCARRERAESP,
		(select url from url_xvii where id = '$Id') url,
		(select descripcion from cat_ur where ur='$UR') CTAREAS_DESCRIPCION
		 FROM rusp_xvii rv
		 where rv.curp = '$CURP' ";

		echo ">$SQL<\n";
		$res = $db->execFetchAll($SQL, "pro_nomina");
		$Contador =8;

		if(is_array($res)){
			foreach ($res as $row){
				$DescPuesto     = strtoupper ($row['DESC_PUESTO']);
				$DenCargo       = strtoupper ($row['DEN_PTO']);
				$AreaUniAds     = strtoupper ($row['CTAREAS_DESCRIPCION']);
				$CVCTNIVEL      = strtolower ($row['CVCTNIVEL']);
				$CVCTCARRERAESP = strtoupper ($row['CVCTCARRERAESP']);
				if (strlen(trim($CVCTNIVEL)) <TRES){
					$CVCTNIVEL      = "ninguno";
					$CVCTCARRERAESP = "";
				}

				$URL = $row['URL'];			
				$Str_10494="";;
				$db_lab = new DbOracle("pro_nomina", "ArchiSoft");


				$SQL_LAB = "select substr(cv.cvlaboral_del,4,8) cvlaboral_del, 
							substr(cv.cvlaboral_al,4,8) cvlaboral_al, cv.cvlaboral_empresa, 
							cv.cvlaboral_puesto,cx.CVCTEXPERIECIA_CAMPO
							from cvlaborales_xvll cv, CVCTEXPERIENCIAS_XVLL cx
							where cv.cvctexperiecia_id = cx.CVCTEXPERIECIA_ID and
							cv.cvdatospersonales_id = '$Id' 
							order by cv.cvlaboral_del desc";

	//			echo "SQL_LAB >>$SQL_LAB<< \n";			

				$res_lab = $db_lab->execFetchAll($SQL_LAB, "pro_nomina");
				foreach ($res_lab as $row_lab) {			
					$CVLABORAL_DEL          = $row_lab['CVLABORAL_DEL'];
					$CVLABORAL_AL           = $row_lab['CVLABORAL_AL'];
					$CVLABORAL_EMPRESA      = strtoupper ($row_lab['CVLABORAL_EMPRESA']);
					$CVLABORAL_PUESTO       = str_replace("|","",strtoupper ($row_lab['CVLABORAL_PUESTO']));
					$CVCTEXPERIECIA_CAMPO   = strtoupper ($row_lab['CVCTEXPERIECIA_CAMPO']);
					$Str_10494 = "$Id|$CVLABORAL_DEL|$CVLABORAL_AL|$CVLABORAL_EMPRESA|$CVLABORAL_PUESTO|$CVCTEXPERIECIA_CAMPO|\n";

					$objPHPExcel->setActiveSheetIndex(3)
			            ->setCellValue('A'.$ContadorTab10494, $Id)
			            ->setCellValue('B'.$ContadorTab10494, $CVLABORAL_DEL)
	   		            ->setCellValue('C'.$ContadorTab10494, $CVLABORAL_AL)
			            ->setCellValue('D'.$ContadorTab10494, utf8_encode($CVLABORAL_EMPRESA))
			            ->setCellValue('E'.$ContadorTab10494, utf8_encode($CVLABORAL_PUESTO))
			            ->setCellValue('F'.$ContadorTab10494, utf8_encode($CVCTEXPERIECIA_CAMPO));
					//$Str_10494= preg_replace('/[^A-Za-z0-9\-\|\s\/\\n\\r\xC1\xC9\xCD\\xD3\xDA]/', '', $Str_10494);
					fwrite ($GestorArchivoTbl , utf8_encode($Str_10494));
					$ContadorTab10494++;

				} // fin foreaach

				$objPHPExcel->setActiveSheetIndex(0)
		            ->setCellValue('A'.$ContadorRow, $Puesto)
		            ->setCellValue('B'.$ContadorRow, $DescPuesto)
   		            ->setCellValue('C'.$ContadorRow, $DenCargo)
		            ->setCellValue('D'.$ContadorRow, $Nombre)
		            ->setCellValue('E'.$ContadorRow, $AppPat)
		            ->setCellValue('F'.$ContadorRow, $AppMat)
		            ->setCellValue('G'.$ContadorRow, $AreaUniAds)
		            ->setCellValue('H'.$ContadorRow, $CVCTNIVEL)
		            ->setCellValue('I'.$ContadorRow, $CVCTCARRERAESP)
		            ->setCellValue('J'.$ContadorRow, $Id)
		            ->setCellValue('K'.$ContadorRow, $URL)
		            ->setCellValue('L'.$ContadorRow, $SancionAdm)
   		            ->setCellValue('M'.$ContadorRow, $FchVal)
		            ->setCellValue('N'.$ContadorRow, $AreaResp)
		            ->setCellValue('O'.$ContadorRow, "2016")
		            ->setCellValue('P'.$ContadorRow, $FchVal)
		            ;

	      	$objValidation = $objPHPExcel->getActiveSheet()->getCell('H'.$ContadorRow)->getDataValidation();
		    $objValidation->setType( PHPExcel_Cell_DataValidation::TYPE_LIST );
		    $objValidation->setErrorStyle( PHPExcel_Cell_DataValidation::STYLE_INFORMATION );
		    $objValidation->setAllowBlank(false);
		    $objValidation->setShowInputMessage(true);
		    $objValidation->setShowErrorMessage(true);
		    $objValidation->setShowDropDown(true);
		    $objValidation->setErrorTitle('Input error');
		    $objValidation->setError('Value is not in list.');
		    //$objValidation->setPromptTitle('Pick from list');
		//    $objValidation->setPrompt('Please pick a value from the drop-down list.');
		    $objValidation->setFormula1("=hidden1"); //note this!

      


				echo "$Puesto|$DescPuesto|$DenCargo|$Nombre|$AppPat|$AppMat|$AreaUniAds|$CVCTNIVEL|$CVCTCARRERAESP|$Id|$URL|$SancionAdm|$FchVal|$AreaResp|2016|$FchVal||\n";
				$ContadorRow++;
			}//fin foreaach
		}
		else{

			echo "$Puesto|$DescPuesto|$DenCargo|$Nombre|$AppPat|$AppMat|$AreaUniAds|$CVCTNIVEL|$CVCTCARRERAESP|$Id|$URL|$SancionAdm|$FchVal|$AreaResp|2016|$FchVal||\n";
		}

		//echo "Id >$Id< Nombre >$Nombre< AppPat >$AppPat< AppMat >$AppMat< CURP >$CURP< Puesto>$Puesto< <br>";
		//print_r($ArrRegistro);
	}// fin del while
}// fin del if (!$GestorArchivo )

$objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, $fileType);
$objWriter->save($fileNameW);

fclose($GestorArchivoTbl);
?>
