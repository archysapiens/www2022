<?php
function cellColor($objPHPExcel,$cells,$color){
//    global $objPHPExcel;

    $objPHPExcel->getActiveSheet()->getStyle($cells)->getFill()->applyFromArray(array(
        'type' => PHPExcel_Style_Fill::FILL_SOLID,
        'startcolor' => array(
             'rgb' => $color
        )
    ));
}


function buscarUrl(){

	$GestorArchivoTbl = fopen($Tabla10494, "r");

if (!$GestorArchivo )
}

?>