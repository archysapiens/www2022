<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//13-oct-2016
// Se agregan condiciones para que en el campo Denominación del cargo
//en caso de que no tenga valor se lñe coloque el valor denominacion del puesto
// Tambien se agrega el valor para el campo Sexo, el cual se extrae de la CURP

// 14 de Octubre
// se implementa en el proceso un array para emitir los formatos para todas las URs

// V4
// 17 de Octubre, se agregan los encabezados del formato.
// ArchySapiens
// Se agregan reglas d elos 40 dias de aguinaldo en celdas Gratificacion Columna Q
// Se agrega la condicion de que los sueldos sean positivos
// Se grega condicion de que las deducciones sean negativas 

// V5
// Se Agrega la funciona lidad para leer el archivo original y ya no darle formato.
//
// V5_detalle
// Con detalle de los estimulos, prestaciones economicas y apoyo economicos.

ini_set('memory_limit', '2048M');
ini_set('max_execution_time', 12000);
require('../general/generales.inc');
require('ac_db_pn.php');
require('Cargar_Remuneraciones_VIII_Central_V4.inc');
$db = new DbOracle("pro_nomina", "ArchiSoft");
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');


//define('EOL',(PHP_SAPI == 'cli') ? PHP_EOL : '<br />');

/** Include PHPExcel */
//echo dirname(__FILE__) . '/../Classes/PHPExcel.php' ." << <br>";
require_once dirname(__FILE__) . '/../transparencia/Classes/PHPExcel.php';
include dirname(__FILE__) . '/../transparencia/Classes/'.'PHPExcel/IOFactory.php';

// para 2015 $Trimestres = array("06" , "12","18"); 
$Trimestres = array("12"); 

// todos incluyendo area central
//$ArrURS = array("CEN" , "E00","N00","V00","X00","K00","L00", "M00","O00","S00","T00","U00","Q00","R00","I00"); 
$ArrURS = array("CEN" );
$ArrTipNom = array("6M","6R","66", "22","11");
$ArrQuincena =array(		"01"  => "10-ENE", 
						"02"  => "25-ENE", 
						"03"  => "10-FEB", 
						"04"  => "25-FEB", 
						"05"  => "10-MAR", 
						"06"  => "25-EMAR", 
						"07"  => "10-ABR", 
						"08"  => "25-ABR", 
						"09"  => "10-MAY", 
						"10"  => "25-MAY", 
						"11"  => "10-JUN", 
						"12"  => "25-JUN", 
						"13"  => "10-JUL", 
						"14"  => "25-JUL", 
						"15"  => "10-AGO", 
						"16"  => "25-AGO", 
						"17"  => "10-SEP", 
						"18"  => "25-SEP", 
						"19"  => "10-OCT", 
						"20"  => "25-OCT", 
						"21"  => "10-NOV", 
						"22"  => "25-NOV", 
						"23"  => "10-DIC", 
						"24"  => "10-DIC", 
						"25"  => "10-DIC");

// SOlo organis deconcentrados
//$ArrURS = array( "E00","N00","V00","X00","K00","L00", "M00","O00","S00","T00","U00","Q00","R00","I00"); 

$styleArray = array(
    'font'  => array(
        'bold'  => true,
        'color' => array('rgb' => 'FFFFFF'),
        'size'  => 12,
        'name'  => 'Arial'
    ));


$styleArrayBorder = array(
  'borders' => array(
    'allborders' => array(
      'style' => PHPExcel_Style_Border::BORDER_THIN
    )
  )
);
// Create new PHPExcel object
//echo date('H:i:s') , " Create new PHPExcel object" , "<br>";
$Anio='2016';
$ImportePrestaciones= CERO;
$DetallePrestaciones="";

foreach ($Trimestres as $Trim) { 

	foreach ($ArrURS as $urs) { 
		$Condicion="XXX";
		switch($urs){
			case "CEN": $Condicion = "bd.ur >='100' and bd.ur <='700'"; break;
			case "E00": $Condicion = "bd.ur ='E00'"; break;
			case "N00": $Condicion = "bd.ur ='N00'"; break;
			case "V00": $Condicion = "bd.ur ='V00'"; break;
			case "X00": $Condicion = "bd.ur ='X00'"; break;
			case "K00": $Condicion = "bd.ur ='K00'"; break;
			case "L00": $Condicion = "bd.ur ='L00'"; break;
			case "M00": $Condicion = "bd.ur ='M00'"; break;
			case "O00": $Condicion = "bd.ur ='O00'"; break;
			case "S00": $Condicion = "bd.ur ='S00'"; break;
			case "T00": $Condicion = "bd.ur ='T00'"; break;
			case "U00": $Condicion = "bd.ur ='U00'"; break;
			case "Q00": $Condicion = "bd.ur ='Q00'"; break;
			case "R00": $Condicion = "bd.ur ='R00'"; break;
			case "I00": $Condicion = "bd.ur ='I00'"; break;

		}// fin del switch

	//	$objReader = PHPExcel_IOFactory::createReader($fileType);
	//	$objPHPExcel = $objReader->load($fileName);


		$objPHPExcel = new PHPExcel();
		$objPHPExcel->getProperties()->setCreator("Secretaria de Salud")
		               ->setLastModifiedBy("Dirección de Automatización de Procesos y Soporte Técnico")
		               ->setTitle("Sistema Nacional de Transparencia")
		               ->setSubject("Sistema Integrador / Vacantes")
		               ->setDescription("Plazas Vacantes del Personal de base y Confianza ")
		               ->setKeywords("Dirección General de Recursos Humanos")
		               ->setCategory("Archivo de Carga Masiva");
		// Add some data
		//echo date('H:i:s') , " Add some data" , EOL;

		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();
		$objPHPExcel->createSheet();

		PHPExcel_Cell::setValueBinder( new PHPExcel_Cell_AdvancedValueBinder() );


		$objPHPExcel->setActiveSheetIndex(0)
					->setCellValueExplicit('A1', '22509',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValue('A2', 'TITULO')
					->setCellValue('B2', 'NOMBRE CORTO')
					->setCellValue('C2', 'DESCRIPCION')					

					->setCellValue('A3', 'Remuneración bruta y neta')
					->setCellValue('B3', 'LGTA70FVIII')
					->setCellValue('C3', 'La información deberá guardar coherencia con lo publicado en cumplimiento de las fracciones II (estructura orgánica), III (facultades de cada área), VII (directorio), IX (gastos de representación y viáticos), X (número total de plazas y del personal de base y confianza), XIII (información de la unidad de transparencia), XIV (convocatorias a concursos para ocupar cargos públicos) y XVII (información curricular) del artículo 70 de la Ley General.')					


					->setCellValueExplicit('A4', '9',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('B4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('C4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('D4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('E4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('F4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('G4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('H4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('I4', '9',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('J4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('K4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('L4', '10',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('M4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('N4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('O4', '10',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('P4', '10',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('Q4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('R4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('S4', '10',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('T4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('U4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('V4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('W4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('X4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('Y4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('Z4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AA4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AB4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AC4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AD4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AE4', '2',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AF4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AG4', '6',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AH4', '4',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AI4', '1',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AJ4', '12',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AK4', '13',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AL4', '14',PHPExcel_Cell_DataType::TYPE_STRING)

					->setCellValueExplicit('A5', '10144',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('B5', '10145',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('C5', '10146',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('D5', '10147',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('E5', '10154',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('F5', '10155',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('G5', '10156',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('H5', '10157',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('I5', '10149',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('J5', '10158',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('K5', '10159',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('L5', '10180',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('M5', '10179',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('N5', '10177',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('O5', '10150',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('P5', '10160',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('Q5', '10162',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('R5', '10161',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('S5', '10181',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('T5', '10164',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('U5', '10163',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('V5', '10166',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('W5', '10165',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('X5', '10168',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('Y5', '10167',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('Z5', '10170',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AA5', '10169',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AB5', '10171',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AC5', '10148',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AD5', '10173',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AE5', '10178',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AF5', '10172',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AG5', '10176',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AH5', '10174',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AI5', '10175',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AJ5', '10152',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AK5', '10151',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValueExplicit('AL5', '10153',PHPExcel_Cell_DataType::TYPE_STRING)
					->setCellValue('A6', 'Tabla Campos')
		            ->setCellValue('A7', 'Tipo de integrante del Sujeto obligado')
		            ->setCellValue('B7', 'Clave o nivel del puesto ')
		            ->setCellValue('C7', 'Denominación del puesto')
		            ->setCellValue('D7', 'Denominación del cargo')
		            ->setCellValue('E7', 'Área de adscripción')
		            ->setCellValue('F7', 'Nombre completo')
		            ->setCellValue('G7', 'Primer apellido')  
					->setCellValue('H7', 'Segundo apellido')  
					->setCellValue('I7', 'Sexo (femenino/Masculino')

		            ->setCellValue('J7', 'Remuneración mensual bruta')
		            ->setCellValue('K7', 'Remuneración mensual neta.')
		            ->setCellValue('L7', 'Percepciones en efectivo:')
		            ->setCellValue('M7', 'Percepciones adicionales o en especie')  
					->setCellValue('N7', 'Periodicidad')  
					->setCellValue('O7', 'Ingresos')

		            ->setCellValue('P7', 'Sistemas de compensación')
		            ->setCellValue('Q7', 'Gratificaciones.')
		            ->setCellValue('R7', 'Periodicidad')
		            ->setCellValue('S7', 'Primas')  

					->setCellValue('T7', 'Comisiones')  
					->setCellValue('U7', 'Periodicidad')

		            ->setCellValue('V7', 'Dietas.')
		            ->setCellValue('W7', 'Periodicidad')
		            ->setCellValue('X7', 'Bonos.')
		            ->setCellValue('Y7', 'Periodicidad')  
					->setCellValue('Z7', 'Estímulos.')  
					->setCellValue('AA7', 'Periodicidad')

		            ->setCellValue('AB7', 'Apoyos económicos.')
		            ->setCellValue('AC7', 'Periodicidad.')
		            ->setCellValue('AD7', 'Prestaciones económicas')
		            ->setCellValue('AE7', 'Prestaciones en especie.')  
					->setCellValue('AF7', 'Periodicidad')  
					->setCellValue('AG7', 'Otro tipo de percepción.')
		            ->setCellValue('AH7', 'Fecha de validación')
		            ->setCellValue('AI7', 'Área responsable de la información')  
					->setCellValue('AJ7', 'Año')  
					->setCellValue('AK7', 'Fecha de actualización')
					->setCellValue('AL7', 'Nota') ;

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

		



		$objPHPExcel->getActiveSheet()->setTitle('hidden1');        
		$objPHPExcel->addNamedRange( 
		        new PHPExcel_NamedRange(
		            'Cargo', 
		            $objPHPExcel->getSheetByName('hidden1'), 
		            'A1:A9'
		        ) 
		    );    

		$objPHPExcel->setActiveSheetIndex(DOS)
		            ->setCellValue('A1', 'Femenino')
		            ->setCellValue('A2', 'Masculino');




		$objPHPExcel->getActiveSheet()->setTitle('hidden2');        
		$objPHPExcel->addNamedRange( 
		        new PHPExcel_NamedRange(
		            'Genero', 
		            $objPHPExcel->getSheetByName('hidden2'), 
		            'A1:A2'
		        ) 
		    );    


		$objPHPExcel->setActiveSheetIndex(TRES)
		            ->setCellValueExplicit('B1', '3',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('B2', '2121',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('C1', '1',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValueExplicit('C2', '2122',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D2', '2123',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValue('A3', 'ID')
		            ->setCellValue('B3', 'Percepción (monto)')
		            ->setCellValue('C3', 'Periodicidad')
		            ->setCellValue('D3', 'Moneda (especificar)')               ;
		$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
		$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
		$objPHPExcel->getActiveSheet()->setTitle('Tabla 10180');            



		$objPHPExcel->setActiveSheetIndex(CUATRO)
		            ->setCellValueExplicit('B1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('B2', '2115',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('C1', '1',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValueExplicit('C2', '2116',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D1', '3',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D2', '2117',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValue('A3', 'ID')
		            ->setCellValue('B3', 'Moneda (especifique)')
		            ->setCellValue('C3', 'Periodicidad')
		            ->setCellValue('D3', 'Ingresos')               ;
		$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
		$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
		$objPHPExcel->getActiveSheet()->setTitle('Tabla 10150');            


		$objPHPExcel->setActiveSheetIndex(CINCO)
		            ->setCellValueExplicit('B1', '3',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('B2', '2118',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('C1', '1',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValueExplicit('C2', '2119',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D2', '2120',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValue('A3', 'ID')
		            ->setCellValue('B3', 'Sistema de compensación')
		            ->setCellValue('C3', 'Periodicidad')
		            ->setCellValue('D3', 'Moneda (especifique)')               ;
		$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
		$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
		$objPHPExcel->getActiveSheet()->setTitle('Tabla 10160');            

		$objPHPExcel->setActiveSheetIndex(SEIS)
		            ->setCellValueExplicit('B1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('B2', '2124',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('C1', '3',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValueExplicit('C2', '2125',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('D2', '2126',PHPExcel_Cell_DataType::TYPE_STRING)   
		            ->setCellValue('A3', 'ID')
		            ->setCellValue('B3', 'Moneda (especifique)')
		            ->setCellValue('C3', 'Primas')
		            ->setCellValue('D3', 'Periodicidad')               ;
		$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
		$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
		$objPHPExcel->getActiveSheet()->setTitle('Tabla 10181');            



		$sql = " select rfc,curp, serpub,cr,ur,puesto,denopuesto,denocargo,nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads, 
		sum(Sueldo) sueldo,sum(dEDUCCIONES) deducciones,sum(PRIMA) prima, sum(Estimulos) estimulos, sum(ApoyoEconomico) apoyoeconomico,sum(PrestacionesEconomicas) prestacioneseconomicas, sum(base) as base
		from (select rfc,curp, 'Servidor Público' as serpub, b.cr, b.ur, b.puesto ,
		(select descripcion from cat_puestos where codigo=b.puesto) as denopuesto,
		case   when indmando in ('10', '20', '30') or puesto like '%CFP%' then 
					(select den_pto from rusp_remu where rfc=b.rfc and rownum=1)
		            else
		              NULL
		            end   as denocargo,
		b.nombre,
		case   when indmando in ('10', '20', '30') or puesto like '%CFP%' then 
		              substr(PUESTO,3,1) ||substr(PUESTO,4,1)|| substr(PUESTO,7,1)
		            else
		              PUESTO
		            end  as nivelpuesto,
		b.QNAPROC, b.LLAVE, b.INDMANDO,b.TIPOTRAB ,           
		(select descripcion from cat_UR where UR=b.UR) as AREAADS,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=1 and  CONCEP in('06', '07','42','55') and PTAANT in ('00','CG','AG') and importe > 0) as Sueldo,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=2 and  CONCEP in('01','02','04') and PTAANT in ('00','52','SI','SR','SP','SS') and importe > 0) as dEDUCCIONES,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=1 and  CONCEP in('32','A1','A2','A3','A4','A5') and PTAANT in ('00','PD','PV','VD')) as PRIMA,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=1 and  CONCEP in('68','69','75') and PTAANT in ('TR','AN','AP','EA')) as Estimulos,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=1 and  CONCEP ='24' and PTAANT='GA') as PeriodicidadEstimulo,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=1 and  CONCEP in('37','45','57') and PTAANT in ('TP','AL','LM') ) as ApoyoEconomico,
		(select sum(importe) from btac$Anio where llave=b.llave and  tconcep=1 and  CONCEP in('59','73') and PTAANT in ('DT','DR','DM') ) as PrestacionesEconomicas,
		nvl((select sum(importe) from btac$Anio where llave=b.llave and  tconcep=2 and  CONCEP in('58')),-1) as base
		from bdac$Anio b
		where b.partida ='11301' and b.INDMANDO not in ('90','80') and b.tipnom IN ('11','6L')  
		and b.QNAPROC='$Trim' and b.tipotrab!='20') bd
		where $Condicion  
		group by rfc, curp,serpub,cr,ur,puesto,denopuesto,denocargo,nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads
		";

		$GestorArchivo = fopen("bdac$Anio.txt", "w");
		if (!$GestorArchivo) {
			echo "Error al abrir archivo Error >>".$Path.$Archivo.".err" ."<<";
		}
		else{
			$res = $db->execFetchAll($sql, "pro_nomina");
			$Contador =8;
			$ImportePrestaciones= CERO;
			$MSG=	"";
			//$MSG=	"NO APLICA DE ACUERDO AL MANUAL DE PERCEPCIONES";
			foreach ($res as $row) {
			//	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";

				//print_r ($row);
				echo "Resgitro Procesado Condicion: $Condicion >>$Contador<< <br>";
				$SerPub =$row['SERPUB'];
				$UR=$row['UR'];
				$CveNiv =$row['NIVELPUESTO'];
				$Puesto=$row['DENOPUESTO'];
				$Denocargo=$row['DENOCARGO'];
				if(strlen(trim($Denocargo))==CERO)
					$Denocargo=$Puesto;
				
				$Nombre=$row['NOMBRE'];
				$CURP = $row['CURP'];
				$Sexo = substr($CURP, 10,1);
				if($Sexo=="H")
					$Sexo="Masculino";
				else
					if($Sexo=="M")
						$Sexo="Femenino";
					else 
						$Sexo= "$Sexo >".$CURP."<";

				$ArrNombre = explode("/",$Nombre);
				if(is_array($ArrNombre)){
					
					if (!isset($ArrNombre[1])){
						//print_r ($ArrNombre);
						$NombreEmpleado = "XXXXXXX";
						$ArrApellidos = "XXXXXXX";
						$ApePaterno =$Nombre;
						$ApeMaterno =$Nombre;
					}
					else{
						$NombreEmpleado = $ArrNombre[1];
						$ArrApellidos = explode(",",$ArrNombre[0]);
						if(is_array($ArrApellidos)){

							$ApePaterno =$ArrApellidos[0]  ;
							if(isset($ArrApellidos[1]))
								$ApeMaterno =$ArrApellidos[1]  ;
							else{
									$NombreEmpleado = "XXXXXXX";
									$ApePaterno =$Nombre ;
									$ApeMaterno =$Nombre ;
								}
						}
						else{
							$NombreEmpleado = "XXXXXXX";
							$ApePaterno =$Nombre ;
							$ApeMaterno =$Nombre ;
						}
					}
				}
				else{
					$NombreEmpleado=$Nombre;
					$ApePaterno =$Nombre;
					$ApeMaterno =$Nombre;
				}

				$EstimuloServidor = buscaEstimulo($CveNiv,$NombreEmpleado,$ApePaterno,$ApeMaterno);
				if(strlen(trim($EstimuloServidor)) > CERO){
					$ArrEstimuloServidor = explode("|", $EstimuloServidor);
					$Estimulo=$ArrEstimuloServidor[CERO];
					$EstimuloDesc=preg_replace('/[^A-Za-z0-9\-\s]/', '',$ArrEstimuloServidor[UNO]);
					 
					//echo "Estimulo UR >$UR< NombreEmpleado>$NombreEmpleado $ApePaterno $ApeMaterno< >$Estimulo<>$EstimuloDesc< <br>";
				}
				else{
					$Estimulo=0;
					$EstimuloDesc="";
				}

				$AreaAds=$row['AREAADS'];
				$PER=floor($row['SUELDO'] *2);
				$NETO=floor(($row['SUELDO'] * 2) - ($row['DEDUCCIONES'] * 2));
				$Prima=floor($row['PRIMA']);
				$TIPOTRAB=$row['TIPOTRAB'];
				$Gratificaciones=$row['DEDUCCIONES'];
				$Estimulos=$row['ESTIMULOS'];	
				//$PeriodicidadEstimulo=$row['PERIODICIDADESTIMULO'];	
				$ApoyoEconomico=$row['APOYOECONOMICO'];	
				$QNAPROC = $row['QNAPROC'];	
				$PrestacionesEconomicas = $row['PRESTACIONESECONOMICAS'];	
				$RFC =$row['RFC'];
				$ApoEcoPer="";
				$PrimaPer="";
				$EstimuloPer="";
				$ApoyoEconomicoPer ="";
				$PrestacionesEconomicasPer="";

				$Base = (int) $row['BASE'];
				//echo " Base >>$Base<< <br>";
				$DetallePrestaciones="\n Detalle del campo Prestaciones económicas Servidor publico No Obtuvo Pretacion de Reyes, Madres o dia del Servidor Publico";
				$ImportePrestaciones =CERO;
				if( $Base > 0){
				//		echo "Seridor Publico de Base <br>";
					    $DetallePrestaciones="";
						$ArrContratos=array();
						
						echo "Seridor Publico de Base>>"	.$Nombre."< <br>";
						$Resultado=obtenPrestacionesPersonalBase($RFC, $CURP);
						$AuxPrestacionesEco="";
						
						foreach ($Resultado as $rowBase) {
							//echo "encontro prestaciones >>$RFC<< >>$CURP<< <br>" ;

							$TIPNOM =$rowBase['TIPNOM'];
							$TCONCEP =$rowBase['TCONCEP'];
							$CONCEP =$rowBase['CONCEP'];
							$PTAANT =$rowBase['PTAANT'];
							$DESCRIPCION =$rowBase['DESCRIPCION'];
							$IMPORTEBASE =$rowBase['IMPORTE'];
							$QNAENVIO =$rowBase['QNAENVIO'];
							if(in_array($TIPNOM, $ArrTipNom)){
								$FechaPago = $ArrQuincena[$QNAENVIO];
								if (isset($ArrContratos[$DESCRIPCION]))
									$ArrContratos[$DESCRIPCION]	=  $ArrContratos[$DESCRIPCION]." Quincena Pago:".$FechaPago." Monto Prestacion: $".$IMPORTEBASE;
								else {
										$ArrContratos[$DESCRIPCION]	= " Quincena Pago:".$FechaPago." Monto Prestacion: $".$IMPORTEBASE;
									}	
								$ImportePrestaciones += $IMPORTEBASE;
							}
							else{ 
								/**
								if(in_array($DESCRIPCION, $ArrContratos)){
									unset($ArrContratos[$DESCRIPCION]);
								}
								**/
								//$ImportePrestaciones -= $IMPORTEBASE;	
							}
							if($ImportePrestaciones > 0)	
								$AuxPrestacionesEco="\n Detalle del campo Prestaciones económicas ";
							
							
						}// find el forreach
						foreach ($ArrContratos as $KKey => $value ) 
							$DetallePrestaciones .= $KKey ." ". $value ."\n";
						$DetallePrestaciones = $AuxPrestacionesEco .$DetallePrestaciones."\n";
						unset($ArrContratos); 
						//	foreach($value as $data => $user_data)    
					     //       $DetallePrestaciones .= " Quincena ". $value . " ".$user_data."\n";


				}// fin del if		


				if ($NombreEmpleado!="XXXXXXX"){

					if($PrestacionesEconomicas > 0){
					 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  pr.DENOMINACION
								from bdac$Anio bd, btac$Anio bt, partida_remu pr
								where bd.rfc=:rfcv and BD.partida ='11301' AND
					            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
					            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
					             $Condicion and
					            bd.llave=bt.llave and          
					            bt.tconcep=1 and  
								bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
								bt.CONCEP in('59','73') and bt.PTAANT in ('DT','DR','DM')";
			        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
			       
				        foreach ($res as $rowIN) {
				        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
				        	$PrestacionesEconomicasPer =$PrestacionesEconomicasPer." " .$rowIN['DENOMINACION']."\n";
				        }	
			     	}
			     	else {
			     	   	$PrestacionesEconomicas= $MSG;
			     	   	$PrestacionesEconomicasPer = $MSG;
			     	   }   

					if($Prima > 0){
					 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  pr.DENOMINACION
								from bdac$Anio bd, btac$Anio bt, partida_remu pr
								where bd.rfc=:rfcv and BD.partida ='11301' AND
					            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
					            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
					              $Condicion and
					            bd.llave=bt.llave and          
					            bt.tconcep=1 and  
								bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
								bt.CONCEP in('32','A1','A2','A3','A4','A5') and bt.PTAANT in ('00','PD','PV','VD')
						";
			        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
			       
				        foreach ($res as $rowIN) {
				        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
				        	$PrimaPer =$PrimaPer." " .$rowIN['DENOMINACION']."\n";
				        }	

				        // Tabla 10181
   				        	  $objPHPExcel->setActiveSheetIndex(SEIS)   
					          ->setCellValue('A'.($Contador-4), $Contador-SIETE)
					          ->setCellValue('B'.($Contador-4), 'Pesos')
					          ->setCellValue('C'.($Contador-4), $Prima)
					          ->setCellValue('D'.($Contador-4), $PrimaPer);

			     	} 
			     	else{
			     	  	$Prima=$MSG;
			     	  	$PrimaPer=$MSG;
			     	  	// Tabla 10181
			        	  $objPHPExcel->setActiveSheetIndex(SEIS)   
					          ->setCellValue('A'.($Contador-4), $Contador-SIETE)
					          ->setCellValue('B'.($Contador-4), 'Pesos')
					          ->setCellValue('C'.($Contador-4), 0)
					          ->setCellValue('D'.($Contador-4), "No tubó Primas en el Periodo");

			     	  }  
			     	  
					if($Estimulos > 0){
					 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  pr.DENOMINACION
								from bdac$Anio bd, btac$Anio bt, partida_remu pr
								where bd.rfc=:rfcv and BD.partida ='11301' AND
					            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
					            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
					             $Condicion and
					            bd.llave=bt.llave and          
					            bt.tconcep=1 and  
								bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
								bt.CONCEP in('68','69','75') and bt.PTAANT in ('TR','AN','AP','EA')
						";
			        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
			       
				        foreach ($res as $rowIN) {
				        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
				        	$EstimuloPer =$EstimuloPer." " .$rowIN['DENOMINACION']."\n";
				        }	
				        $EstimuloPer ="Detalle de la columna Periodicidad del estimulo ". $EstimuloPer ."\n";
			     	} 
			     	else{
			     	  	$Estimulos=$MSG;
			     	  	$EstimuloPer=$MSG;
			     	  }  
		     	  	$Estimulos +=$Estimulo;
		     	  	$EstimuloPer = $EstimuloPer ." " .$EstimuloDesc ."\n";
		     	  	//ECHO "EstimuloPer >$EstimuloPer< <BR>";

 

					if($ApoyoEconomico > 0){
					 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  
					 			case when bt.PTAANT = 'TP' then 
					 			 			pr.DENOMINACION ||' (Unica Vez)'
					 			when bt.PTAANT in ('AL','LM') then 
					 			 			pr.DENOMINACION ||' (Anual)' 			
					 			 end  as 	DENOMINACION2		
								from bdac$Anio bd,btac$Anio bt, partida_remu pr
								where bd.rfc=:rfcv and BD.partida ='11301' AND
					            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
					            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
					             $Condicion  and
					            bd.llave=bt.llave and   
					            bt.tconcep=1 and  
								bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
								bt.CONCEP in('37','45','57') and bt.PTAANT in ('TP','AL','LM')
								";
			        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
			       
				        foreach ($res as $rowIN) {
				        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
				        	$ApoyoEconomicoPer =$ApoyoEconomicoPer." ".$rowIN['DENOMINACION2']."\n";
				        }	
			     	} 
			     	else{
			     	  	$ApoyoEconomico=$MSG;
			     	  	$ApoyoEconomicoPer=$MSG;
			     	  }  


				  $currencyFormat = '_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)';
				  $objPHPExcel->getActiveSheet()->getStyle('J'.($Contador))->getNumberFormat()->setFormatCode($currencyFormat);	
				  
				  //$currencyFormat = '_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)';
				  //$objPHPExcel->getActiveSheet()->getStyle('K'.($Contador))->getNumberFormat()->setFormatCode($currencyFormat);	

			      $objPHPExcel->setActiveSheetIndex(0)
		            ->setCellValue('A'.($Contador), $SerPub)
		            ->setCellValueExplicit('B'.$Contador, $CveNiv,PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValue('C'.$Contador, $Puesto)
		            ->setCellValueExplicit('D'.$Contador, $Denocargo,PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('E'.$Contador, $AreaAds,PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValue('F'.$Contador, $NombreEmpleado)
		            ->setCellValue('G'.$Contador, $ApePaterno)
		            ->setCellValue('H'.$Contador, $ApeMaterno)
		            ->setCellValue('I'.$Contador, $Sexo)
		            ->setCellValue('J'.($Contador), $PER)
		            ->setCellValue('k'.($Contador), $NETO)
//		            ->setCellValue('L'.$Contador, $Contador-SIETE)
		            ->setCellValue('L'.$Contador, 1)
		            ->setCellValueExplicit('M'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
		            ->setCellValueExplicit('N'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
//no envia datos	->setCellValue('O'.$Contador, $Contador-SIETE)
					->setCellValue('O'.$Contador, 1)
//		            ->setCellValue('P'.$Contador, $Contador-SIETE)
					->setCellValue('P'.$Contador, 1)
		            ->setCellValue('Q'.$Contador, 40)
					->setCellValue('R'.$Contador, "Anual")
					->setCellValue('S'.$Contador, $Contador-SIETE)
					->setCellValue('T'.$Contador, "")
		            ->setCellValue('U'.$Contador, $MSG)
		            ->setCellValue('V'.$Contador, $MSG)
					->setCellValue('W'.$Contador, $MSG)
		            ->setCellValue('X'.$Contador, $MSG)
					->setCellValue('Y'.$Contador, $MSG)
            
		            ->setCellValue('Z'.$Contador, $Estimulos)
		            ->setCellValue('AA'.$Contador, $EstimuloPer)
		            ->setCellValue('AB'.$Contador, $ApoyoEconomico)
		            ->setCellValue('AC'.$Contador, $ApoyoEconomicoPer)
		            ->setCellValue('AD'.$Contador, $ImportePrestaciones)
		            ->setCellValue('AE'.$Contador, "")          
		            ->setCellValue('AF'.$Contador, $MSG)          
		            ->setCellValue('AG'.$Contador, $MSG)
				->setCellValue('AH'.$Contador, '2016-06-30')
				->setCellValue('AI'.$Contador, 'DIRECCIÓN GENERAL DE RECURSOS HUMANO')
				->setCellValue('AJ'.$Contador, $Anio)                        
				->setCellValue('AK'.$Contador, '2016-06-30')
				->setCellValue('AM'.$Contador,$DetallePrestaciones. $EstimuloPer);                        

	$objValidation = $objPHPExcel->getActiveSheet()->getCell('I'.$Contador)->getDataValidation();
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
    $objValidation->setFormula1("=Genero"); //note this!



	$objValidation = $objPHPExcel->getActiveSheet()->getCell('A'.$Contador)->getDataValidation();
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
    $objValidation->setFormula1("=Cargo"); //note this!



//				->setCellValue('AL'.$Contador, 'Se tienen campos pendientes de integrar información');

			$objPHPExcel->getActiveSheet()->getStyle('AH'.$Contador)->getNumberFormat()->setFormatCode(PHPExcel_Style_NumberFormat::FORMAT_DATE_YYYYMMDDSLASH);
			$objPHPExcel->getActiveSheet()->getStyle('AK'.$Contador)->getNumberFormat()->setFormatCode(PHPExcel_Style_NumberFormat::FORMAT_DATE_YYYYMMDDSLASH);

		//->setCellValue('AE'.$Contador, $PrestacionesEconomicasPer)    

		// Tabla 10180
		         $PosCol=4;   
		         $objPHPExcel->setActiveSheetIndex(TRES)   
		          ->setCellValue('A'.$PosCol, 1)
		          ->setCellValue('B'.$PosCol, CERO)
		          ->setCellValue('C'.$PosCol, 'Mensual')
		          ->setCellValue('D'.$PosCol, 'Pesos');

		// Tabla 10150

		         $objPHPExcel->setActiveSheetIndex(CUATRO)   
		          ->setCellValue('A'.$PosCol, 1)
		          ->setCellValue('B'.$PosCol, 'Pesos')
		          ->setCellValue('C'.$PosCol, 'Mensual')
		          ->setCellValue('D'.$PosCol, CERO);

		//Tabla 10160


		         $objPHPExcel->setActiveSheetIndex(CINCO)   
		          ->setCellValue('A'.$PosCol, 1)
		          ->setCellValue('B'.$PosCol, 'Pago')
		          ->setCellValue('C'.$PosCol, 'Mensual')
		          ->setCellValue('D'.$PosCol, 'Pesos');

			


		       
		$Contador++;
				}		

				
			//	fwrite($GestorArchivo, $Str);
		}	// fin del for reach de extraccionde datos

		$objPHPExcel->setActiveSheetIndex(0);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('A')
		                ->setAutoSize(true);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('B')
		                ->setAutoSize(true);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('C')
		                ->setAutoSize(true);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('D')
		                ->setAutoSize(true);

		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('E')
		                ->setAutoSize(true);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('F')
		                ->setAutoSize(true);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('T')
		                ->setAutoSize(true);
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('AL')
		                ->setAutoSize(true);
                
		$objPHPExcel->getActiveSheet()
		                ->getColumnDimension('AM')
		                ->setAutoSize(true);


		cellColor($objPHPExcel,'A6:AL6', '2B2B2B');
		cellColor($objPHPExcel,'A2:C2', '2B2B2B');

		$objPHPExcel->getActiveSheet()->getStyle("A6:AL6")->getFont()->setBold(true)
                                ->setName('Arial')
                                ->setSize(11)
                                ->getColor()->setRGB('FFFFFF');

		$objPHPExcel->getActiveSheet()->getStyle("A2:C2")->getFont()->setBold(true)
                                ->setName('Arial')
                                ->setSize(11)
                                ->getColor()->setRGB('FFFFFF');


        cellColor($objPHPExcel,'A7:AL7', 'E1E1E1');                        
        cellColor($objPHPExcel,'A3:C3', 'E1E1E1');

		$objPHPExcel->getActiveSheet()->getStyle('A7:AL7')->applyFromArray($styleArrayBorder);

		$objPHPExcel->getActiveSheet()->getStyle('A1')->applyFromArray($styleArray);
		$objPHPExcel->getActiveSheet()->getStyle('B1')->applyFromArray($styleArray);
		$objPHPExcel->getActiveSheet()->getStyle('c1')->applyFromArray($styleArray);

		$objPHPExcel->getActiveSheet()->getStyle('D1')->applyFromArray($styleArray);
		$objPHPExcel->getActiveSheet()->getStyle('E1')->applyFromArray($styleArray);
		$objPHPExcel->getActiveSheet()->getStyle('F1')->applyFromArray($styleArray);
		$objPHPExcel->getActiveSheet()->getStyle('G1')->applyFromArray($styleArray);

		$objPHPExcel->getActiveSheet()->getRowDimension(1)->setVisible(FALSE);
		$objPHPExcel->getActiveSheet()->getRowDimension(4)->setVisible(FALSE);
		$objPHPExcel->getActiveSheet()->getRowDimension(5)->setVisible(FALSE);

		$objPHPExcel->setActiveSheetIndex(0)->mergeCells('A6:AL6');
		$objPHPExcel->getActiveSheet()->getStyle('A6:AL6')->getAlignment()->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER);

		$objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
		//$objWriter->save(str_replace('.php', '.xlsx', __FILE__));
		$objWriter->save($Anio."_".$Trim."_"."$urs"."_VIII_Remuneraciones Brutas y Netas.xlsx");

		//	fclose($GestorArchivo);
		
	}
 }// fin foreach urs	
}// foreach
?>		        