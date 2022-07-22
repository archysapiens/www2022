<?php

function obtenPrestacionesPersonalBase($RFC, $CURP){
	$db = new DbOracle("pro_nomina", "ArchiSoft");
 $SQL = "select bt.rfc, bd.qnaenvio, bd.TIPNOM,bt.TCONCEP,bt.CONCEP, bt.ptaant,    cc.descripcion, bt.IMPORTE
		from bdac2016 bd, btac2016 bt, cat_cpto_2016 cc
		where  bd.llave=bt.llave and
		bt.TCONCEP =cc.tipo and 
		bt.CONCEP= cc.concepto and 
		bt.ptaant = cc.ptaant and 
		bt.TCONCEP=1 and bt.CONCEP in ('73','59') and 
		bt.ptaant in ('DR','DM','DT') and
		bt.rfc='$RFC' and bd.TIPNOM in ('6R','66', '22','77','6M','11','6T')
		order by bd.TIPNOM, bt.ptaant";	

//echo "obtenPrestacionesPersonalBase >>$SQL<< <br>";

$res = $db->execFetchAll($SQL, "Query Example");

return $res;
}// fin de obtenPrestacionesPersonalBase



function cellColor($objPHPExcel,$cells,$color){
//    global $objPHPExcel;

    $objPHPExcel->getActiveSheet()->getStyle($cells)->getFill()->applyFromArray(array(
        'type' => PHPExcel_Style_Fill::FILL_SOLID,
        'startcolor' => array(
             'rgb' => $color
        )
    ));
}


function buscaEstimulo($CvePto, $Nombre,$AppPat, $AppMat){
$GestorArchivo = fopen("Productividad.txt", "r");
$EstimuloEncontrado="";
if (!$GestorArchivo){
	echo "Error al abrir archivo Error |estructura.txt" ."|";
}
else{
	 while (($Registro = fgets($GestorArchivo, 4096)) !== false)  {
    	 $CvePtoLoc="";
    	 $NombreLoc="";
    	 $AppPatLoc="";
    	 $AppMatLoc="";
    	 
    	 $ArrRegistro = explode("|",$Registro);

    	 $CvePtoLoc=$ArrRegistro[CERO];
    	 $NombreLoc=$ArrRegistro[UNO];
    	 $AppPatLoc=$ArrRegistro[DOS];
    	 $AppMatLoc=$ArrRegistro[TRES];
    	 $Estimulo=$ArrRegistro[CUATRO];
    	 $EstimuloDesc=$ArrRegistro[CINCO];
    	 if(trim($CvePtoLoc)==trim($CvePto) and trim($NombreLoc)==trim($Nombre) and 
    	 	trim($AppPatLoc)==trim($AppPat) and trim($AppMatLoc)==trim($AppMat) ){
    	 	$EstimuloEncontrado=$Estimulo. "|".$EstimuloDesc."|";
    	 	break;
    	 }


   } // fin de while	 

   fclose($GestorArchivo);
} // fin de if (!$GestorArchivo) 
return $EstimuloEncontrado;
}// fin de buscaEstimulo


?>