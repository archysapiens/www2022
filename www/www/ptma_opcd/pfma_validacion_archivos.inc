<?php

/*************************************************************
* 
*  Funcion : obtenProcesosPlanificados
*  Objetivo: Obtiene los archivos que estan por planificarse
*            
*  Fecha   : 16-May-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdPlanificacion : Identificación de la remesa
*  Valor de regreso : Vector con archivos
*
***************************************************************/   

function obtenProcesosPlanificados($IdPlanificacion){
	$db = new DbCnnx();   
	$SQL= "SELECT   fecha_evento,   id_remesas,   archivo_procesado
			FROM ssa.bitacora
			where id_remesas = $IdPlanificacion
			and estatus='P'";
	//echo "pfma_validacion_archivos.inc/obtenProcesosPlanificados/ SQL>>".$SQL."<< <br>";		
	$Rows = $db->select($SQL);
	if(!$Rows){
		echo "<br>pfma_validacion_archivos.inc/obtenProcesosPlanificados/No existe Remesa autorizada <br>";
	}	
	else{	
		return $Rows;
	}// fin de if
}// fin de obtenProcesosPlanificados

/*************************************************************
* 
*  Funcion : planificaProceso
*  Objetivo: Planifica el proceso de validacion y carga
*            
*            
*  Fecha   : 03-May-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdEstado : Identificación del Organismo
*   $Anio     : Anio del perido(2016, 2017, 2018,etc)
*   $Prdiodo  : Quincena procesada(Q1, Q2, Q3, etc.)
*   $TipoArch : Tipo del Archivo a procesar(1-X00, 2-416, 3-610, etc.)   
*   $LogValidacion : Es una rchivo en donde quedaron asentadas las 
*                    validaciones realizadas. 
*   $EstatusPlan: Este parametro nos indica que registro en bitacora 
*                  se realizara:
*                  CERO  : Planifica el proceso
*                  -UNO  : Resgitra Error en formato Archivo
*  Valor de regreso
*
***************************************************************/   

function planificaProceso($IdEstado,$Anio,$Periodo,$TipoArchivo,$LogValidacion, $EstatusPlan,$IdTry)
{ 
/**
echo "registraValidacion ";
echo "IdEstado >$IdEstado<   <br>"; 
echo "Anio >$Anio<   <br>"; 
echo "Periodo >$Periodo<   <br>"; 
echo "TipoArchivo >$TipoArchivo<   <br>"; 
echo "LogValidacion >$LogValidacion<   <br>"; 
echo "EstatusPlan >$EstatusPlan<   <br>"; 
echo "IdTry >$IdTry<   <br>"; 
**/
$RemesaPlanificada=0;
$db = new DbCnnx();   
/*
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("Ymd");
$HoraProceso = date("His");
$FechaProceso =$FechaProceso.$HoraProceso;
*/
$FechaProceso=substr($IdTry,8,14);

$LogValidacionTmp =$LogValidacion;
$PathArray=explode("/",$LogValidacion);
$RenTmp =$PathArray[count($PathArray)-UNO];
//echo "RenTmp >>$RenTmp<< <br>";
$RenTmp2=$FechaProceso.$RenTmp;
//echo "RenTmp2 >>$RenTmp2<< <br>";
//echo "Antes LogValidacion >>$LogValidacion<< <br>";
$LogValidacion = str_replace($RenTmp, $RenTmp2, $LogValidacion);
//echo "Despues LogValidacion >>$LogValidacion<< <br>";


$FechaProceso = $db->quote($FechaProceso);
$IdEdo = $db->quote($IdEstado);
$LogToLoad = $db->quote($LogValidacion);
$StrMsg = "Planificacion";
$StrEstat="P";
if($EstatusPlan != CERO){
	$StrMsg = "Error ZIP";
	$StrEstat="E";
}
$StrPlan=$db->quote($StrMsg);
$StrEstat=$db->quote($StrEstat);




if(!rename($LogValidacionTmp, $LogValidacion))
	echo "pfma_validacion_archivos/rename";

$SQL = " SELECT	  id FROM remesas WHERE id_organismos=" . $IdEdo . " AND  
			estatus='A' AND id_archivos= " . $TipoArchivo . " AND 
			anio_periodos=". $Anio . " AND numero_periodos = ". $Periodo ;
//echo "planificaProceso/SQL Remesa>" .$SQL ."< <br>";
$rows = $db->select($SQL);
if(!$rows){
	echo "<br>pfma_validacion_archivos.inc/planificaProceso/No existe Remesa autorizada <br>";
	$RemesaPlanificada=0;
}	
else{	
		$IdValidacion =  CERO;
		$Contador=  CERO;
		while(isset($rows[$Contador]['id'])){
			$IdValidacion = $rows[$Contador]['id'] ;

			$Contador++;
		}// fin de while	
		$RemesaPlanificada=$IdValidacion;
	    $SQL ="INSERT INTO bitacora (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%Y%m%d%H%i%s')," . $IdValidacion .",". $LogToLoad .",". CERO .",".
		$StrPlan .",". $StrPlan. ",".$StrPlan.",". $StrPlan.",1," .$StrEstat .")";
		//echo "Segundo SQL CERO >". $SQL ."< <br>";
		$rows = $db->select($SQL);
  }	// fin de existencia de remesa I  
  return $RemesaPlanificada;
}// fin de planificaProceso





/*************************************************************
* 
*  Funcion : registraValidacion
*  Objetivo: Registra el resultado de la validacion en
*            la bitacora de validaciones
*            
*  Fecha   : 22-Abr-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdEstado : Identificación del Organismo
*   $Anio     : Anio del perido(2016, 2017, 2018,etc)
*   $Prdiodo  : Quincena procesada(Q1, Q2, Q3, etc.)
*   $TipoArch : Tipo del Archivo a procesar(1-X00, 2-416, 3-610, etc.)   
*   $LogValidacion : Es una rchivo en donde quedaron asentadas las 
*                    validaciones realizadas. 
*   $TipoRegistro: Este parametro nos indica que registro en bitacora 
*                  se realizara:
*                  CERO  : Resgistro de validacion Exitosa
*                  -UNO  : Registro, formato de archivo erroneo
*                  > CERO: Errores en campos
*  Valor de regreso
*
***************************************************************/   

function registraValidacion($IdEstado,$Anio,$Periodo,$TipoArchivo,$LogValidacion,$TipoRegistro)
{ 
/**	
echo "registraValidacion ";
echo "IdEstado >$IdEstado<   <br>"; 
echo "Anio >$Anio<   <br>"; 
echo "Periodo >$Periodo<   <br>"; 
echo "TipoArchivo >$TipoArchivo<   <br>"; 
echo "LogValidacion >$LogValidacion<   <br>"; 
echo "TipoRegistro >$TipoRegistro<   <br>"; 
**/
$db = new DbCnnx();   
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("d-m-Y");
$HoraProceso = date("H:i:s");
$FechaProceso =$FechaProceso." ".$HoraProceso;
$FechaProceso = $db->quote($FechaProceso);
$IdEdo = $db->quote($IdEstado);
$LogToLoad = $db->quote($LogValidacion);
$SQL = " SELECT	  id FROM remesas WHERE id_organismos=" . $IdEdo . " AND  
			estatus='A' AND id_archivos= " . $TipoArchivo . " AND 
			anio_periodos=". $Anio . " AND numero_periodos = ". $Periodo ;
//echo "SQL Remesa>" .$SQL ."< <br>";
$rows = $db->select($SQL);
if(!$rows)
	echo "<br>pfma_validacion_archivos.inc/registraValidacion/No existe Remesa autorizada<br>";
else{	
		$IdValidacion =  CERO;
		$Contador=  CERO;
		while(isset($rows[$Contador]['id'])){
			$IdValidacion = $rows[$Contador]['id'] ;
			$Contador++;
		}// fin de while	
		//echo "<br> IdValidacion >" . $IdValidacion . "< <br>";
		//echo "<br> TipoRegistro >" . $TipoRegistro . "< <br>";
	
	if($TipoRegistro > CERO) {
		$GestorArchivoErr = fopen($LogValidacion, "r");
		if ($GestorArchivoErr){
		   while (($RegistroErr=fgets($GestorArchivoErr, 4096))!==false){
		    	$ArrRegistroErr = explode("|",$RegistroErr);
		    	$StrErr = $db->quote($ArrRegistroErr[3]);
		    	$StrCampo = $db->quote($ArrRegistroErr[1]);
		    	$StrDes = $db->quote($ArrRegistroErr[3]);
		    	$BanderaRegistr=CERO;
	        	$ArrRegistroErr = explode("|",$RegistroErr);
		        $SQL ="INSERT INTO BITACORA (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,
				 estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%d-%m-%Y %H:%i:%s')," . $IdValidacion .",". $LogToLoad .",". $ArrRegistroErr[0] .",".
					  $StrErr .",". $StrCampo. ",".$StrDes.",". $StrCampo.",1,'E')";
					 // echo "Segundo SQL >". $SQL ."< <br>";
				$rows = $db->select($SQL);
		    } //fin del while   
		}// fin Gestor Archvio	
 	}elseif($TipoRegistro ==CERO){	
		$StrOK=$db->quote("Sin Error");
	    $SQL ="INSERT INTO BITACORA (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%d-%m-%Y %H:%i:%s')," . $IdValidacion .",". $LogToLoad .",". CERO .",".
		$StrOK .",". $StrOK. ",".$StrOK.",". $StrOK.",1,'K')";
		//echo "Segundo SQL CERO >". $SQL ."< <br>";
		$rows = $db->select($SQL);
	}elseif($TipoRegistro < CERO){
		$StrOK=$db->quote("Error de Formato de Archivos");
	    $SQL ="INSERT INTO BITACORA (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%d-%m-%Y %H:%i:%s')," . $IdValidacion .",". $LogToLoad .",". CERO .",".
		$StrOK .",". $StrOK. ",".$StrOK.",".$StrOK.",1,'F')";
		//echo "Segundo SQL >". $SQL ."< <br>";
		$rows = $db->select($SQL);
	}
  }	// fin de existencia de remesa I  
}// fin de registraValidacion

/*************************************************************
* 
*  Funcion : validaCamposArchivo
*  Objetivo: Validar el numero de cmapos que tiene el archivo
*            
*  Fecha   : 12-Abr-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $Archivo : Rutay nombre de archivo a validar
*
***************************************************************/   

function validaCamposArchivo($Archivo)
{
	$ValRegreso=FALLA;
	if (!copy($Archivo, $Archivo.".bak")) {
    	echo "Error al copiar $Archivo  <br>";
		$ValRegreso=FALLA;
	}
	else{
		$GestorArchivo = fopen($Archivo.".bak", "r");
		if ($GestorArchivo){
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	//  83 echo " validaCamposArchivo >" .substr_count($Registro, '|') ."< <br>";
		    	if(  substr_count($Registro, '|') > 70)
		    		$ValRegreso=DATA_NOMINA;
		    	elseif(substr_count($Registro, '|') < 70)
		    		$ValRegreso=DATA_NOMINA_TRAILER;
		    	else
		    		$ValRegreso=FALLA;
	    		break;
		    }// fin del while	
		    fclose($GestorArchivo);
		 }    
		 else
		 	return FALLA;
	}// fin copy
	return $ValRegreso;
} // function validaCamposArchivo($Archivo)

/*************************************************************
* 
*  Funcion : validateDate
*  Objetivo: Validar formatos de Fecha
*            
*  Fecha   : 11-Abr-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $Fecha : Fecha a Validar
*   $Formato     : aaaammdd
*
***************************************************************/   

function validateDate($Fecha, $Formato = 'Ymd')
{
    $d = DateTime::createFromFormat($Formato, $Fecha);
    return $d && $d->format($Formato) == $Fecha;
}



/*************************************************************
* 
*  Funcion : fncValidaArchivo
*  Objetivo: Validar el archivo de datos
*            
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   $Path     : Ruta de ubicacion 
*   $Archivo  : Archivo dedatos a validar
*   
*
***************************************************************/   

function fncValidaArchivo($IdEstado, $Path,$Archivo)
{
	$TotalRegErr      = CERO;
 	$ContadorRegistros=UNO;
 	$TotalRegErrParcial =CERO;
 	
 	$ContadorErrorDI = InicializaArray(100);


 	$GestorArchivoErr = fopen($Path.$Archivo.".err", "w");
 	if (!$GestorArchivoErr) 
	{
		echo "Error al abrir archivo Error >>".$Path.$Archivo.".err" ."<<";
	}
	else{
		$ArchivoDatos = $Path.$Archivo;
		$ValidaError= fncValidaDC6($IdEstado, $GestorArchivoErr, $ArchivoDatos);

		if($ValidaError!=0){
				$ContadorErrorDI[DIEZ * OCHO + SEIS]++;
		}

		$GestorArchivo = fopen($Path.$Archivo, "r");
		if ($GestorArchivo) 
		{
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	$BanderaRegistr=0;
		   //     echo "Resgistro >>" . $Registro ."<<";
		        $ArrRegistro = explode("|",$Registro);
		        $NumEmpl= $ArrRegistro[CERO];
		        $NumFili= $ArrRegistro[UNO];
		        $CURP= $ArrRegistro[DOS];

		        $NombreEmpleado = $ArrRegistro[3];
		        $BancoNvo= $ArrRegistro[SEIS];
		        $NumCta = $ArrRegistro[SIETE];
		        $CLABE= $ArrRegistro[OCHO];
		        $CveSPC= $ArrRegistro[NUEVE];
		        $UR= $ArrRegistro[14];
		        $GF= $ArrRegistro[15];
		        $Fun= $ArrRegistro[16];
		        $SFun= $ArrRegistro[17];
		        $PG= $ArrRegistro[18];
		        $AI= $ArrRegistro[19];
		        $PP= $ArrRegistro[20];
		        $Ptda= $ArrRegistro[21];
		        $Pto= $ArrRegistro[22];
		        $NumPto= $ArrRegistro[23];
		        $Edo= $ArrRegistro[24];
		        $Mpio= $ArrRegistro[25];
		        $CenRes= $ArrRegistro[26];
		        $NSS= $ArrRegistro[27];
		        $Pagdria= $ArrRegistro[28];
		        $FteFin = $ArrRegistro[29];
		        $TabPto = $ArrRegistro[30];
		        $NIVEL = $ArrRegistro[31];
		        $Rango = $ArrRegistro[32];
		        $IndMando = $ArrRegistro[33];
		        $Horario = $ArrRegistro[34];
		        // el campo 36 queda libre
		        $TipTra = $ArrRegistro[36];
		        $NivSPC= $ArrRegistro[37];
		        $IndStat= $ArrRegistro[38];
		        $FecIng= $ArrRegistro[39];
		        $FecIngSS= $ArrRegistro[40];
		        $FecReIng= $ArrRegistro[41];
				$FecPag= $ArrRegistro[43];

				$PerPagIni= $ArrRegistro[44];
				$PerPagFin= $ArrRegistro[45];
				$PerAppIni= $ArrRegistro[46];
				$PerAppFin= $ArrRegistro[47];

				

				$QnaProReal= $ArrRegistro[48];
				$AnioProReal= $ArrRegistro[49];

				$TipoPago = $ArrRegistro[50];
				// no va (52) Instrumento de Pago Anterior  (Libre) 
				$IntrPagoNvo = $ArrRegistro[52];
				$Prpcns = $ArrRegistro[53];
				$Dedcns = $ArrRegistro[54];
				$Neto = $ArrRegistro[55];
				$NumTrail = $ArrRegistro[56];
				$NomProd = $ArrRegistro[58];
				$NumCtrl = $ArrRegistro[59];
				$NumCque = $ArrRegistro[60];
				// no hay regla 61
				$Jnda    = $ArrRegistro[62];
				// no hay 63 Número de Días de Prima Dominical (Libre)
				$CicloFONAC = $ArrRegistro[64];
				$NumAportFONAC= $ArrRegistro[65];
				$AcumuladoFONAC= $ArrRegistro[66];
				// no hay 67 Número de faltas en la quincena (Libre)
				$LicCLUES = $ArrRegistro[68];

				$PorcPen1 = $ArrRegistro[69];
				$PorcPen2 = $ArrRegistro[70];
				$PorcPen3 = $ArrRegistro[71];
				$PorcPen4 = $ArrRegistro[72];
				$PorcPen5 = $ArrRegistro[73];

				$ElecTipRtro = $ArrRegistro[74];				
				$TipUni = $ArrRegistro[75];				
				$DescCR = $ArrRegistro[76];				

		        $ValidaError = fncValidaDI_1($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumEmpl);
		        if($ValidaError!=0){
					$ContadorErrorDI[UNO]++;		        	
				}
//break;
				$ValidaError = fncValidaDI_2($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumFili, $NombreEmpleado);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DOS]++;
				}
				
				$ValidaError = fncValidaDI_3($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CURP, $NombreEmpleado);	
		        if($ValidaError!=0){
					$ContadorErrorDI[TRES]++;		        	
				}


				$ValidaError = fncValidaDI_4($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NombreEmpleado);	
		        if($ValidaError!=0){
					$ContadorErrorDI[CUATRO]++;
				}

				$ValidaError = fncValidaDI_7($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $BancoNvo);	
		        if($ValidaError!=0){
					$ContadorErrorDI[SIETE]++;
				}

				$ValidaError = fncValidaDI_8($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumCta);	
		        if($ValidaError!=0){
					$ContadorErrorDI[OCHO]++;        	
				}

				$ValidaError = fncValidaDI_9($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CLABE);	
		        if($ValidaError!=0){
					$ContadorErrorDI[NUEVE]++;
				}

				$ValidaError = fncValidaDI_10($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CveSPC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ]++;
				}

				$EstructuraProg = $UR . $GF .$Fun. $SFun. $PG. $AI. $PP;



				$ValidaError = fncValidaDC1_15_21_EP($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $EstructuraProg, $UR);	
		        if($ValidaError!=0){
					$ContadorErrorDI[OCHO * DIEZ + UNO]++;
				}



				$ValidaError = fncValidaDI_22($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Ptda);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DOS]++;
				}
				$ValidaError = fncValidaDI_23($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Pto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + TRES]++;
				}

				$ValidaError = fncValidaDI_24($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumPto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CUATRO]++;
				}

				$ValidaError = fncValidaDI_25($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Edo);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CINCO]++;
				}

				$ValidaError = fncValidaDI_26($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Mpio);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SEIS]++;
				}

				$ValidaError = fncValidaDI_27($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CenRes);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDI_28($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NSS);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDI_29($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Pagdria);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDI_30($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FteFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ]++;
				}

				$ValidaError = fncValidaDI_31($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TabPto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDI_32($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NIVEL);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DOS]++;
				}
				$ValidaError = fncValidaDI_33($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Rango);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + TRES]++;
				}

				$ValidaError = fncValidaDI_34($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IndMando);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + CUATRO]++;
				}
				$ValidaError = fncValidaDI_35($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Horario);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + CINCO]++;
				}

				// campo 36 queda libre

				$ValidaError = fncValidaDI_37($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TipTra);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + SIETE]++;
				}

				// 2. DIRECTIVA DE CALIDAD PARA PENSIONADOS
				$ValidaError = fncValidaDC2($IdEstado, $GestorArchivoErr, $ContadorRegistros, $TipTra);
		        if($ValidaError!=0){
					$ContadorErrorDI[OCHO*DIEZ + DOS]++;
				}



				$ValidaError = fncValidaDI_38($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NivSPC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDI_39($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IndStat);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDI_40($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecIng);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ]++;
				}


				$ValidaError = fncValidaDI_41($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecIngSS, $FecIng);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDI_42($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecReIng,$FecIngSS);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ DOS]++;
				}

				$ValidaError = fncValidaDI_44($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecPag);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ CUATRO]++;
				}

				$ValidaError = fncValidaDI_45($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerPagIni,$PerPagFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ CINCO]++;
				}


				$ValidaError = fncValidaDI_46($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerPagFin, $PerPagIni);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ SEIS]++;
				}

				$ValidaError = fncValidaDI_47($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerAppIni, $PerAppFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ SIETE]++;
				}


				$ValidaError = fncValidaDI_48($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerAppFin, $PerAppIni);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ OCHO]++;
				}

				$ValidaError = fncValidaDI_49($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $QnaProReal);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ NUEVE]++;
				}


				$ValidaError = fncValidaDI_50($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $AnioProReal,$PerPagIni,$PerPagFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO]++;
				}


				$ValidaError = fncValidaDC4($IdEstado, $GestorArchivoErr, $ContadorRegistros, $PerPagIni,$PerPagFin, $QnaProReal, $AnioProReal);
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * OCHO + CUATRO]++;
				}


				$ValidaError = fncValidaDI_51($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $TipoPago);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + UNO]++;
				}

				$ValidaError = fncValidaDI_53($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $IntrPagoNvo);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + TRES]++;
				}

				$ValidaError = fncValidaDI_54($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Prpcns);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + CUATRO]++;
				}

				$ValidaError = fncValidaDI_55($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Dedcns);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + CINCO]++;
				}

				$ValidaError = fncValidaDI_56($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Neto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + SEIS]++;
				}

				$ValidaError = fncValidaDI_57($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumTrail);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + SIETE]++;
				}

				$ValidaError = fncValidaDI_59($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NomProd);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + NUEVE]++;
				}

				$ValidaError = fncValidaDI_60($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumCtrl);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS]++;
				}

				$ValidaError = fncValidaDI_61($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumCque);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + UNO]++;
				}
				$ValidaError = fncValidaDI_63($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Jnda);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + TRES]++;
				}

				$ValidaError = fncValidaDI_65($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $CicloFONAC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + CINCO]++;
				}

				$ValidaError = fncValidaDI_66($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumAportFONAC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + SEIS]++;
				}

				$ValidaError = fncValidaDI_67($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $AcumuladoFONAC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + SIETE]++;
				}

				$ValidaError = fncValidaDI_69($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $LicCLUES );	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + NUEVE]++;
				}

				$ValidaError = fncValidaDC8($IdEstado, $GestorArchivoErr, $UR, $LicCLUES);
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * OCHO + OCHO]++;
				}



				$ValidaError = fncValidaDI_70($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen1  );	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE ]++;
				}

				$ValidaError = fncValidaDI_71($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen2  );	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + UNO]++;
				}

				$ValidaError = fncValidaDI_72($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen3);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + DOS]++;
				}

				$ValidaError = fncValidaDI_73($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen4);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + TRES]++;
				}

				$ValidaError = fncValidaDI_74($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen5);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + CUATRO]++;
				}

				$ValidaError = fncValidaDI_75($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $ElecTipRtro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + CINCO]++;
				}

				$ValidaError = fncValidaDI_76($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $TipUni);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + SEIS]++;
				}

				$ValidaError = fncValidaDI_77($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $DescCR);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + SIETE]++;
				}
		
		        $ContadorRegistros++;

		        if(($ContadorRegistros % 1000) ==CERO){
					    foreach ($ContadorErrorDI as &$valorParcial) {
			 				   		$TotalRegErrParcial = $TotalRegErrParcial + $valorParcial ;
						}
						if ($TotalRegErrParcial > 1000)
							break;
	        	}


		    }

		    foreach ($ContadorErrorDI as &$valor) {
 				   		$TotalRegErr = $TotalRegErr + $valor ;
			}
            /**
		    if (!feof($GestorArchivo)) {
		        echo "Error: fallo inesperado de fgets()\n";
		        $TotalRegErr=FALLA;
		    }
		    **/
		    fclose($GestorArchivo);
		} // fin Gestor archivo de datos
	} //Fin  if (!$GestorArchivoErr) 
	return $TotalRegErr;
}// fin de la funcion fncValidaArchivo


function InicializaArray($Limite){
		for($i = 1; $i <= $Limite; $i++) 
		{ 
		    ${'array'}[$i] = 0; 
		} 
	return $array;
} // fin de InicializaArray


/*************************************************************
* 
*  Funcion : fncValidaDI_1
*  Objetivo: Validar el campo Número de Empleado
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr :Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_1($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_1           = "(1) Numero Empleado";
	$DI_1_ErrTam    = "Tamaño de registro debe ser 10";
	$DI_1_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_1_ErrIdEmpl = "Número de Empleado Invalido";

	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	if (strlen($LocCampo) == DIEZ)
	{
		$ValidaIdEstado = substr($LocCampo,0,2);
		if($ValidaIdEstado != $IdEstado)
		{
			$Error = $NumReg ."|".$DI_1."|".$LocCampo."|" . $DI_1_ErrIdEdo." ($IdEstado)|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}
		if(!preg_match ("/\d{8}/" ,substr($LocCampo,2,8)))
		{
			$Error = $NumReg ."|".$DI_1."|".$LocCampo."|" . $DI_1_ErrIdEmpl."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
	/**
		$Error = $NumReg ."|".$DI_1."|".$Campo."|" . $DI_1_ErrTam."|" .strlen(preg_replace('/[^A-Za-z0-9\-]/', '', $Campo))."|\n";
    **/
		$Error = $NumReg ."|".$DI_1."|".$Campo."|" . $DI_1_ErrTam."|\n";
		
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_1



/*************************************************************
* 
*  Funcion : fncValidaDI_2
*  Objetivo: Validar el campo Número de Empleado
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_2($IdEstado, $GestorErr, $NumReg, $Campo,$CampoAux)
{
	 
	$Bandera = 0;

	$DI_2           = "(2) Filiación";
	$DI_2_ErrTam    = "Tamaño de registro debe ser 13 Caracteres";
	$DI_2_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_2_ErrRFC = "RFC Incorrecto en Sección I AAAA";
	$DI_2_ErrFecNac = "RFC Incorrecto en Sección II Fecha Nacimiento";
	$DI_2_ErrHomoCve = "RFC Incorrecto en Sección III Homoclave";


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";
	$MtrxStrAux = explode("/", $CampoAux);
	$MtrxStrAuxApp = explode(",", $MtrxStrAux[CERO]);
	$AppPat		= (isset($MtrxStrAuxApp[CERO]))?$MtrxStrAuxApp[CERO]:"" ;
	$AppMat     = (isset($MtrxStrAuxApp[UNO]))?$MtrxStrAuxApp[UNO]:"";
	$NomEmpl    = (isset($MtrxStrAux[UNO]))?$MtrxStrAux[UNO]:"";
/**	
	echo "AppPat >$AppPat< <br>";
	echo "AppMat >$AppMat< <br>";
	echo "Nombre >$NomEmpl< <br>";
**/	
    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == 13)
	{

		if(!preg_match ("/[A-Z,a-z]{4}/" ,substr($LocCampo,0,4)))
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrRFC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrFecNac ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(strlen(substr($LocCampo,10,3)) != TRES)
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrHomoCve ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_2."|".$Campo."|" . $DI_2_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_2


/*************************************************************
* 
*  Funcion : fncValidaDI_3
*  Objetivo: Validar el campo CURP
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_3($IdEstado, $GestorErr, $NumReg, $Campo,$CampoAux)
{
	 
	$Bandera = 0;
/**	
	$CatEdo = array("AS" , "BC","BS", "CC", "CL", "CM","CS", "CH", "DF", 
				"DG", "GT", "GR", "HG", "JC", "MC","MN", "MS", "NT", "NL", "OC",
				"PL", "QT", "QR", "SP","SL", "SR", "TC", "TS", "TL","VZ", "YN", "ZS", "NE");
**/
 	global $CatEdo;
	$DI_3           = "(3) Clave Única de Registro de Población (CURP)";
	$DI_3_ErrTam    = "Tamaño de registro debe ser 18 Caracteres";
	$DI_3_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_3_ErrRFC = "CURP Incorrecto en Sección I AAAA";
	$DI_3_ErrFecNac = "CURP Incorrecto en Sección II Fecha Nacimiento";
	$DI_3_ErrGenero = "CURP Incorrecto en Sección III Genero";
	$DI_3_ErrEntFecNac= "CURP Incorrecto en Sección IV Entidad Federativa Nacimeinto";


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";
	$MtrxStrAux = explode("/", $CampoAux);
	$MtrxStrAuxApp = explode(",", $MtrxStrAux[CERO]);
	$AppPat		= (isset($MtrxStrAuxApp[CERO]))?$MtrxStrAuxApp[CERO]:"" ;
	$AppMat     = (isset($MtrxStrAuxApp[UNO]))?$MtrxStrAuxApp[UNO]:"";
	$NomEmpl    = (isset($MtrxStrAux[UNO]))?$MtrxStrAux[UNO]:"";
/**	
	echo "AppPat >$AppPat< <br>";
	echo "AppMat >$AppMat< <br>";
	echo "Nombre >$NomEmpl< <br>";
**/	
    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == 18)
	{

		if(!preg_match ("/[A-Z,a-z]{4}/" ,substr($LocCampo,0,4)))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrRFC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrFecNac ."|$CampoAux\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(!preg_match ("/[M|H|m|h]{1}/" ,substr($LocCampo,10,1)))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrGenero ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		if(!in_array(substr($LocCampo,11,2), $CatEdo))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrEntFecNac ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_3


/*************************************************************
* 
*  Funcion : fncValidaDI_4
*  Objetivo: Validar el campo Nombre Empleado
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_4($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_4           = "(4) Nombre del Empleado";
	$DI_4_ErrTam    = "Tamaño de registro debe ser 150 Caracteres";
	$DI_4_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_4_ErrEstructura = "EL campo no cumple con estructura definida PATERNO,MATERNO/NOMBRE(S)";

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) <= 150)
	{
		if(!preg_match ("/[&,?,A-Z,a-z,\s]{1,90},[&,?,A-Z,a-z,\s]{1,90}\/[&,?.A-Z,a-z,\s]{1,90}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_4."|".$LocCampo."|" . $DI_4_ErrEstructura."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_4."|".$LocCampo."|" . $DI_4_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_4


/***
Las directivas 5 y 6 estan en definición.

***/



/*************************************************************
* 
*  Funcion : fncValidaDI_7
*  Objetivo: Validar el campo Banco Nuevo
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_7($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_7           = "(7)Banco Nuevo";
	$DI_7_ErrTam    = "Tamaño de registro debe ser 5 dígitos";
	$DI_7_TESOFE  = "Identificador no pertenece al Catalogo de TESOFE/DGRH";

//	$TESOFE = explode("\n", file_get_contents('catalogo_tesofe.txt'));


	global $TESOFE;

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 5)
	{
		if(!in_array($LocCampo,$TESOFE))
		{
			$Error = $NumReg ."|".$DI_7."|".$LocCampo."|" . $DI_7_TESOFE."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_7."|".$LocCampo."|" . $DI_7_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_7

/*************************************************************
* 
*  Funcion : fncValidaDI_8
*  Objetivo: Validar el campo Numero de Cuenta
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_8($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_8           = "(8)Numero de Cuenta";
	$DI_8_ErrTam    = "Tamaño de Numero de Cuenta debe ser 16 dígitos";
	$DI_8_NumCta    = "No cumple con Directiva debe ser 16 digitos";

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 16)
	{
		if(!preg_match ("/\d{16}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_NumCta."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_8



/*************************************************************
* 
*  Funcion : fncValidaDI_9
*  Objetivo: Validar el campo Clave del Banco (CLABE)
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_9($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_9           = "(9)Clave del Banco (CLABE)";
	$DI_9_ErrTam    = "Tamaño de Clave del Banco (CLABE) debe ser 18 dígitos";
	$DI_9_NumCta    = "No cumple con Directiva debe ser 18 digitos";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 18)
	{
		if(!preg_match ("/\d{18}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_9_NumCta."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_9."|".$LocCampo."|" . $DI_9_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_9



/*************************************************************
* 
*  Funcion : fncValidaDI_10
*  Objetivo: Validar el campo Clave del Servicio Profesional de Carrera (FUNCION)
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_10($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_10           = "(10)Clave del Servicio Profesional de Carrera (FUNCION)";
	$DI_10_ErrTam    = "Tamaño de Clave del Servicio Profesional de Carrera (FUNCION) debe ser 2 dígitos";
	$DI_10_CveInda   = "La cleve debe ser de 2 digitos";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match ("/\d{2}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_10."|".$LocCampo."|" . $DI_10_CveInda."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_10."|".$LocCampo."|" . $DI_10_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_10

/*************************************************************
* 
*  Funcion : fncValidaDI_15_21_EP
*  Objetivo: Validar la estructura programatica            
*  Fecha   : 23-Nov-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_15_21_EP($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_15           = "(15)Unidad Responsable";
	$DI_15_ErrTam    = "Tamaño de UR debe ser Alfanumérico a 3 posiciones";
	$DI_15_UR   = "La UR no es parte del catalogo de DGRH";

	//$UR = explode("\n", file_get_contents('catalogo_ur.txt'));


  	
  	global $UR;
    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$UR))
		{
			$Error = $NumReg ."|".$DI_15."|".$LocCampo."|" . $DI_15_UR."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_15."|".$LocCampo."|" . $DI_15_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_15




/*************************************************************
* 
*  Funcion : fncValidaDI_22 
*  Objetivo: Validar el campo Partida

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_22($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_22           = "(22)Partida";
	$DI_22_ErrTam    = "Tamaño de Actividad Institucional debe ser  a 5 Alfanumerico";
	$DI_22_Ptda   	 = "La Partida no es parte del catalogo de DGRH";
	
    $Ptda= array("44106","12301","11301");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CINCO)
	{
		if(!in_array($LocCampo,$Ptda))
		{
			$Error = $NumReg ."|".$DI_22."|".$LocCampo."|" . $DI_22_Ptda."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_22."|".$LocCampo."|" . $DI_22_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_22


/*************************************************************
* 
*  Funcion : fncValidaDI_23 
*  Objetivo: Validar el campo Puesto

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_23($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_23           = "(23)Puesto";
	$DI_23_ErrTam    = "Tamaño de Puesto debe ser  a 7 Alfanumerico";
	$DI_23_Pto   	 = "El Puesto no es parte del catalogo de DGRH";
	global $Pto;
	
	$LocCampo =$Campo;
	if (in_array($LocCampo,$Pto))	{
		$Bandera = CERO;
	}
	else
	{
		$Error = $NumReg ."|".$DI_23."|".$LocCampo."|" . $DI_23_Pto."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_23

/*************************************************************
* 
*  Funcion : fncValidaDI_24 
*  Objetivo: Validar el campo Numero de Puesto

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_24($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_24           = "(24)Número de Puesto";
	$DI_24_ErrTam    = "Tamaño de Número de Puesto debe ser  a 4 Alfanumerico";
	$DI_24_NumPto   	 = "El Número Puesto no es parte del catalogo de DGRH";
	
    $NumPto= array("0022","0101");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO)
	{
		if(!in_array($LocCampo,$NumPto))
		{
			$Error = $NumReg ."|".$DI_24."|".$LocCampo."|" . $DI_24_NumPto."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_24."|".$LocCampo."|" . $DI_24_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_24

/*************************************************************
* 
*  Funcion : fncValidaDI_25 
*  Objetivo: Validar el campo Estado

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_25($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_25           = "(25)Estado";
	$DI_25_ErrTam    = "Tamaño de Estado debe ser  a 2 Dígitos";
	$DI_25_Edo    	 = "El Estado no es parte del catalogo de DGRH";

    global $Edo;
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo,$Edo))
		{
			$Error = $NumReg ."|".$DI_25."|".$LocCampo."|" . $DI_25_Edo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_25."|".$LocCampo."|" . $DI_25_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_25

/*************************************************************
* 
*  Funcion : fncValidaDI_26 
*  Objetivo: Validar el campo Municipio

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_26($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_26           = "(26) Municipio";
	$DI_26_ErrTam    = "Tamaño de campo Municipio debe ser  a 3 Dígitos";
	$DI_26_Mpio    	 = "El Municipio no es parte del catalogo de DGRH";
	
	// agregar catalogo de Municpios
	
	global $Mpio;
	$Tam = count($Mpio);

	$LocCampo = $Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$Mpio))
		{
			$Error = $NumReg ."|".$DI_26."($Tam)($IdEstado)"."|".$LocCampo."|" . $DI_26_Mpio."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_26."|".$LocCampo."|" . $DI_26_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_26

/*************************************************************
* 
*  Funcion : fncValidaDI_27 
*  Objetivo: Validar el campo Centro de Responsabilidad

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_27($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_27           = "(27)Centro de Responsabilidad";
	$DI_27_ErrTam    = "Tamaño de campo Centro de Responsabilidad debe ser  a 10 Caracters";
	$DI_27_Edo    	 = "El Centro de Responsabilidad no corresponde al Estado";
	$DI_27_CR    	 = "El Centro de Responsabilidad no corresponde al catalogo de DGRH";
	
	// agregar catalogo de Municpios
    $Edo= array($IdEstado);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ)
	{
		if(!in_array(substr($LocCampo,0,2),$Edo))
		{
			$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_Edo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if(!preg_match("/\d{8}/",substr($LocCampo,2,8)))
		{
			$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_CR."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_27


/*************************************************************
* 
*  Funcion : fncValidaDI_28 
*  Objetivo: Validar el campo Cédula de Identidad (NSS)

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_28($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_28           = "(28)Cédula de Identidad (NSS)";
	$DI_28_ErrTam    = "Tamaño de campo Cédula de Identidad (NSS) debe ser  a 11 Caracters";
	$DI_28_NSS    	 = "La Cédula de Identidad (NSS) no corresponde (80)";
	$DI_28_ISSSTE   	 = "La Cédula de Identidad (NSS) no corresponde al asignado pór ISSSTE";
	
	// agregar catalogo de Municpios
	$LocCampo =$Campo;
	if (strlen($LocCampo) == (DIEZ + UNO))
	{
		if(!(substr($LocCampo,0,2) == "80"))
		{
			$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_NSS."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if(!preg_match("/\d{9}/",substr($LocCampo,2,9)))
		{
			$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_ISSSTE."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_28

/*************************************************************
* 
*  Funcion : fncValidaDI_29 
*  Objetivo: Validar el campo Pagaduria

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_29($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_29           = "(29)Pagaduria";
	$DI_29_ErrTam    = "Tamaño de campo Pagaduria debe ser  a 5 Caracters";
	$DI_29_Pgria   	 = "Pagaduria no corresponde las reglas de negocio establecidas por DGRH";
	
	
	// agregar catalogo de Municpios
	$LocCampo =$Campo;
	if (strlen($LocCampo) == CINCO)
	{
		if(!preg_match("/[A-Za-z0-9]{5}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_29."|".$LocCampo."|" . $DI_29_Pgria."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_29."|".$LocCampo."|" . $DI_29_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_29

/*************************************************************
* 
*  Funcion : fncValidaDI_30 
*  Objetivo: Validar el campo Número de AHISA - Fuente de Financiamiento

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_30($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_30           = "(30)Número de AHISA-Fuente de Financiamiento";
	$DI_30_ErrTam    = "Tamaño de campo Número de AHISA-Fuente de Financiamiento debe ser de 2 Digítos";
	$DI_30_noDI   	 = "Número de AHISA - Fuente de Financiamiento no corresponde las reglas de negocio establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_30."|".$LocCampo."|" . $DI_30_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_30."|".$LocCampo."|" . $DI_30_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_30

/*************************************************************
* 
*  Funcion : fncValidaDI_31 
*  Objetivo: Validar el campo Tabulador de Puesto

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_31($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_31           = "(31)Tabulador de Puesto";
	$DI_31_ErrTam    = "Tamaño de campo Tabulador de Puesto debe ser de 3 Digítos";
	$DI_31_noDI   	 = "Tabulador de Puesto no corresponde las Directivas Institucionales  establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!preg_match("/[0-9]{3}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_31."|".$LocCampo."|" . $DI_31_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_31."|".$LocCampo."|" . $DI_31_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_31

/*************************************************************
* 
*  Funcion : fncValidaDI_32 
*  Objetivo: Validar el campo Nivel de puesto - NIVEL

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_32($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_32           = "(32)Nivel de puesto - NIVEL";
	$DI_32_ErrTam    = "Nivel de puesto - NIVEL debe ser de 2 Digítos";
	$DI_32_noDI   	 = "Nivel de puesto - NIVEL no corresponde las Directivas Institucionales  establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_32."|".$LocCampo."|" . $DI_32_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_32."|".$LocCampo."|" . $DI_32_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_32

/*************************************************************
* 
*  Funcion : fncValidaDI_33 
*  Objetivo: Validar el campo Rango

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_33($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_33           = "(33)Rango";
	$DI_33_ErrTam    = "Rango debe ser de 1 Digítos";
	$DI_33_noDI   	 = "Rango no corresponde las Directivas Institucionales  establecidas por DGRH (1,2,3)";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match("/[0-9]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_33."|".$LocCampo."|" . $DI_33_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_33."|".$LocCampo."|" . $DI_33_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_33


/*************************************************************
* 
*  Funcion : fncValidaDI_34
*  Objetivo: Validar el campo Indicador de Mando

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_34($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_34           = "(34)Indicador de Mando";
	$DI_34_ErrTam    = "Indicador de Mando debe ser de 2 Digítos";
	$DI_34_noDI   	 = "Indicador de Mando no corresponde al catalogo establecidas por DGRH";
	
	$IndMando = array("01","08","10","30","50","60","70","75","80","90");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo, $IndMando))
		{
			$Error = $NumReg ."|".$DI_34."|".$LocCampo."|" . $DI_34_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_34."|".$LocCampo."|" . $DI_34_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_34

/*************************************************************
* 
*  Funcion : fncValidaDI_35
*  Objetivo: Validar el campo Horario Asignado

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_35($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_35           = "(35)Horario Asignado";
	$DI_35_ErrTam    = "Horario Asignado debe ser de 1 Digítos";
	$DI_35_noDI   	 = "Horario Asignado no corresponde al catalogo establecidas por DGRH(1-8)";
	
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match("/[1-8]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_35."|".$LocCampo."|" . $DI_35_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_35."|".$LocCampo."|" . $DI_35_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_35


/*************************************************************
* 
*  Funcion : fncValidaDI_37
*  Objetivo: Validar el campo Tipo de Trabajador

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_37($IdEstado, $GestorErr, $NumReg, $Campo)
{
	global $ProductoNomina; 
	$Bandera = CERO;

	$DI_37           = "(37)Tipo de Trabajador";
	$DI_37_ErrTam    = "Tipo de Trabajador debe ser de 2 Digítos";
	$DI_37_noDI   	 = "Tipo de Trabajador no corresponde al catalogo establecidas por DGRH(01,11,20)";
	$DI_37_noPen   	 = "Tipo de Trabajador no corresponde al tipo de Nomina Pensionados";
	
	

	$LocCampo =$Campo;

	if($LocCampo == "20"){
		if (!preg_match("/9[0-9,A-Z,a-z]/{1}",$ProductoNomina)){
				$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_noPen."|\n";
				fwrite($GestorErr, $Error);
				$Bandera = UNO;
		}
	}
	else {
		if (strlen($LocCampo) == DOS)
		{
			if(!preg_match("/[0-9]{2}/",$LocCampo))
			{
				$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_noDI."|\n";
				fwrite($GestorErr, $Error);
				$Bandera = UNO;
			}	
		}
		else
		{
			$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_ErrTam."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}	
	return $Bandera;
} // fin de funcion fncValidaDI_37


/*************************************************************
* 
*  Funcion : fncValidaDI_38
*  Objetivo: Validar el campo Nivel de puesto - Nivel de puesto SPC

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_38($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_38           = "(38)Nivel de puesto - Nivel de puesto SPC";
	$DI_38_ErrTam    = "Nivel de puesto - Nivel de puesto SPC debe ser de 10 Digítos";
	$DI_38_noDI   	 = "Nivel de puesto - Nivel de puesto SPC no corresponde al catalogo establecidas por DGRH";
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ)
	{
		if(!preg_match("/[0-9]{10}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_38."|".$LocCampo."|" . $DI_38_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_38."|".$LocCampo."|" . $DI_38_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_38

/*************************************************************
* 
*  Funcion : fncValidaDI_39
*  Objetivo: Validar el campo Indicador del Empleado - Estatus del Empleado

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_39($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_39           = "(39)Indicador del Empleado - Estatus del Empleado";
	$DI_39_ErrTam    = "Indicador del Empleado - Estatus del Empleado debe ser de 1 Digíto";
	$DI_39_noDI   	 = "Indicador del Empleado - Estatus del Empleado no corresponde al catalogo establecido por DGRH(0,1,4)";

	$IndEmpl = array("0","2","1","4","3");	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!in_array($LocCampo, $IndEmpl))
		{
			$Error = $NumReg ."|".$DI_39."|".$LocCampo."|" . $DI_39_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_39."|".$LocCampo."|" . $DI_39_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_39


/*************************************************************
* 
*  Funcion : fncValidaDI_40
*  Objetivo: Validar el campo Fecha de Ingreso al Gobierno Federal

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_40($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_40           = "(40)Fecha de Ingreso al Gobierno Federal";
	$DI_40_ErrTam    = "Fecha de Ingreso al Gobierno Federal debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_40_noDI   	 = "Fecha de Ingreso al Gobierno Federal no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";

		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_40."|".$LocCampo."|" . $DI_40_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_40."|".$LocCampo."|" . $DI_40_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_40

/*************************************************************
* 
*  Funcion : fncValidaDI_41
*  Objetivo: Validar el campo Fecha de Ingreso a la Secretaría de Salud

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_41($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_41           = "(41)Fecha de Ingreso a la Secretaría de Salud";
	$DI_41_ErrTam    = "Fecha de Ingreso a la Secretaría de Salud debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_41_noDI   	 = "Fecha de Ingreso a la Secretaría de Salud no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_41_FecIng 	 = "Fecha de Ingreso a la Secretaría de Salud no puede ser menor a Fecha de Ingreso al Gobierno Federal";
		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($Campo2);
			$Fecha2 = date_create($LocCampo);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )< CERO)
			{
					$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_FecIng."|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_41

/*************************************************************
* 
*  Funcion : fncValidaDI_42
*  Objetivo: Validar el campo Fecha de Reingreso

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_42($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_42           = "(42)Fecha de Reingreso";
	$DI_42_ErrTam    = "Fecha de Reingreso debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_42_noDI   	 = "Fecha de Reingreso no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_42_FecIng 	 = "Fecha de Reingreso no puede ser menor a Fecha de Ingreso al Gobierno Federal";
		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($Campo2);
			$Fecha2 = date_create($LocCampo);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a')) < CERO)
			{
					$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_FecIng."|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_42

// campo 43 sin Directiva Institucional

/*************************************************************
* 
*  Funcion : fncValidaDI_44
*  Objetivo: Validar el campo Fecha de Pago
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_44($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_44           = "(44)Fecha de Pago";
	$DI_44_ErrTam    = "Fecha de Pago debe ser de 9 Caracteres(DDMMMAAAA (AAAA=año, MM=mes(primeras 3 letras), DD=día))";
	$DI_44_noDI   	 = "Fecha de Pago no corresponde al formato establecido por DGRH(DDMMMAAAA DD=día, MM=mes(primeras 3 letras), AAAA=año)";
	$DI_44_FecIng 	 = "Fecha de Pago no puede ser menor a Fecha de Ingreso al Gobierno Federal";
	$MesValido=array("ENE","FEB","MAR","ABR","MAY","JUN","JUL","AGO","SEP", "OCT","NOV","DIC");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == NUEVE)
	{
		$Dia =substr($LocCampo,0,2);
		$Mes =substr($LocCampo,2,3);
		$Anio=substr($LocCampo,5,4);
		$Resultado = array_search(strtoupper($Mes), $MesValido);		
		if  (strlen($Resultado) <= 0)
		{
			$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;

		}	
		$Fecha =$Anio.str_pad(((int) $Resultado) +1,2,"0",STR_PAD_LEFT).$Dia;

		if(!validateDate($Fecha))
		{
			$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else
	{
		$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_44


// 30-May-2016

/*************************************************************
* 
*  Funcion : fncValidaDI_45
*  Objetivo: Validar el campo Periodo de Pago Inicial
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_45($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_45           = "(45)Periodo de Pago Inicial";
	$DI_45_ErrTam    = "Periodo de Pago Inicial ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_45_noDI   	 = "Periodo de Pago Inicial no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_45_PerFinal 	 = "Periodo de Pago Inicial no puede ser posterior a Periodo de Pago Final";		
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_45."|".$LocCampo."|" . $DI_45_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )< CERO)
			{
					$Error = $NumReg ."|".$DI_45."|".$LocCampo."|" . 
					$DI_45_PerFinal ."(" .$LocCampo." )(". $Campo2.")|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_45."|".$LocCampo."|" . $DI_45_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_45


/*************************************************************
* 
*  Funcion : fncValidaDI_46
*  Objetivo: Validar el campo Periodo de Pago Final
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_46($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_46           = "(46)Periodo de Pago Final";
	$DI_46_ErrTam    = "Periodo de Pago Final ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_46_noDI   	 = "Periodo de Pago Final no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_46_PerFinal  = "El perido final no puede ser menor al Periodo Inicial";	
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_46."|".$LocCampo."|" . $DI_46_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )> CERO)
			{
					$Error = $NumReg ."|".$DI_46."|".$LocCampo."|" . 
					$DI_46_PerFinal."(". $LocCampo . ")(". $Campo2 .")|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_46."|".$LocCampo."|" . $DI_46_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_46


/*************************************************************
* 
*  Funcion : fncValidaDI_47
*  Objetivo: Validar el campo Periodo de Aplicación Inicial
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_47($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_47           = "(47)Periodo de Aplicación Inicial";
	$DI_47_ErrTam    = "Periodo de Aplicación Inicial ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_47_noDI   	 = "Periodo de Aplicación Inicial no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_47_PerAppIni 	 = "Periodo de Aplicación Inicial no puede ser posterior a Periodo de Aplicacion Final";		
	$DI_47_AppIni="No Corresponde a datos de Aplicacion Inicial (01 o 16)";
	$DI_47_PerAppAnioMes="Mes y Año no corresponder con la Directiva de Calidad Establecida por la DGRH";
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )< CERO)
			{
					$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . 
					"$DI_47_PerFinal($LocCampo)($Campo2)" ."|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
		$Dia =substr($LocCampo,6,2);
		if($Dia != "01" and $Dia != "16" )
		{
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_AppIni."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		if(substr($LocCampo,0,6) != substr($Campo2,0,6))
		{
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . 
			$DI_47_PerAppAnioMes ."(" . $LocCampo .")(". $Campo2.")|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else
	{
		$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_47


/*************************************************************
* 
*  Funcion : fncValidaDI_48
*  Objetivo: Validar el campo Periodo de Aplicación Final
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_48($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2){
	 
	$Bandera = CERO;

	$DI_48           = "(48)Periodo de Aplicación Final";
	$DI_48_ErrTam    = "Periodo de Aplicación Final ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_48_noDI   	 = "Periodo de Aplicación Final no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_48_PerAppIni 	 = "Periodo de Aplicación Final no puede ser Anterior a Periodo de Aplicacion Inicial";		
	$DI_48_AppIni="No Corresponde a datos de Aplicacion Final (15/28/29/30/31)";
	$DI_48_PerAppAnioMes="Mes y Año no corresponder con la Directiva de Calidad Establecida por la DGRH";

	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO){
		if(!validateDate($LocCampo)){
			$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . $DI_48_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2)){
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )> CERO){
					$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . 
					$DI_48_PerFinal ."( " . $LocCampo. ")(". $Campo2 .")|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	

		$Dia =substr($LocCampo,6,2);
		if($Dia != "15" and $Dia != "30" ){
			$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . $DI_48_AppIni."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(substr($LocCampo,0,6) != substr($Campo2,0,6)){
			$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . 
								"$DI_48_PerAppAnioMes ($LocCampo)($Campo2)"."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else{
		$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . $DI_48_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_48


/*************************************************************
* 
*  Funcion : fncValidaDI_49
*  Objetivo: Validar el campo Quincena de Proceso Real
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_49($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;

	$DI_49           = "(49)Quincena de Proceso Real";
	$DI_49_ErrTam    = "Quincena de Proceso Real ser de 2 digitos";
	$DI_49_Qna   	 = "La quincena no corresponde a la Directiva de Calidad deifinida por la DGRH(01-24)";

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS){

		if((int)$LocCampo <1 and (int)$LocCampo > 24){
			$Error = $NumReg ."|".$DI_49."|".$LocCampo."|" . $DI_49_Qna."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

	}
	else{
		$Error = $NumReg ."|".$DI_49."|".$LocCampo."|" . $DI_49_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_49


/*************************************************************
* 
*  Funcion : fncValidaDI_50
*  Objetivo: Validar el campo Año de Proceso Real
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_50($IdEstado, $GestorErr, $NumReg, $Campo, $PerIni,$PerFin){
	 
	$Bandera = CERO;
	$DI_50           = "(50)Año de Proceso Real";
	$DI_50_ErrTam    = "Año de Proceso Real ser de 4 digitos";
	$DI_50_Anio   	 = "No se aceptan años posteriores a año de periodo de pago inicial y perido de pago final ";

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO){
		if((int)$LocCampo > (int)substr($PerIni,CERO,CUATRO) OR 
					(int)$LocCampo > (int)substr($PerFin,CERO,CUATRO)){
			$Error = $NumReg ."|".$DI_50."|".$LocCampo."|" . $DI_50_Anio."($PerIni,$PerFin)|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else{
		$Error = $NumReg ."|".$DI_50."|".$LocCampo."|" . $DI_50_ErrTam."($PerIni,$PerFin)|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_50

/*************************************************************
* 
*  Funcion : fncValidaDI_51
*  Objetivo: Validar el campo Tipo de Pago
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_51($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_51           = "(51)Tipo de Pago";
	$DI_51_ErrTam    = "Tipo de Pago ser de 1 digitos";
	$DI_51_Catalogo    = "El valor no coincide con la directiva de calidad de la DGRH";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO){
		if(!preg_match("/[0-8]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_51."|".$LocCampo."|" . $DI_51_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_51."|".$LocCampo."|" . $DI_51_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_51


/*************************************************************
* 
*  Funcion : fncValidaDI_53
*  Objetivo: Validar el campo Instrumento de Pago Nuevo
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_53($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_53             = "(53)Instrumento de Pago Nuevo";
	$DI_53_ErrTam      = "Instrumento de Pago Nuevo ser de 2 digitos";
	$DI_53_Catalogo    = "El valor de Instrumento de Pago Nuevo no coincide con la directiva de calidad de la DGRH";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS){
		if($LocCampo != "02" and $LocCampo != "05" )
		{
			$Error = $NumReg ."|".$DI_53."|".$LocCampo."|" . $DI_53_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_53."|".$LocCampo."|" . $DI_53_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_53


/*************************************************************
* 
*  Funcion : fncValidaDI_54
*  Objetivo: Validar el campo Percepciones 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_54($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_54             = "(54)Percepciones ";
	$DI_54_ErrTam      = "Percepciones debe  ser de 10 digitos y 2 decimales";
	$DI_54_Catalogo    = "Percepciones no coincide con la directiva de calidad de la DGRH(9999999999.99)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[0-9]{8}.[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_54."|".$LocCampo."|" . $DI_54_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_54."|".$LocCampo."|" . $DI_54_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_54




/*************************************************************
* 
*  Funcion : fncValidaDI_55
*  Objetivo: Validar el campo Deducciones
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_55($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_55             = "(55)Deducciones ";
	$DI_55_ErrTam      = "Deducciones debe  ser de 10 digitos y 2 decimales ";
	$DI_55_Catalogo    = "Deducciones no coincide con la directiva de calidad de la DGRH(9999999999.99)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[0-9]{8}.[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_55."|".$LocCampo."|" . $DI_55_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_55."|".$LocCampo."|" . $DI_55_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_55

/*************************************************************
* 
*  Funcion : fncValidaDI_56
*  Objetivo: Validar el campo Neto
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_56($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_56           = "(56)Neto";
	$DI_56_ErrTam    = "Neto debe  ser de 10 digitos y 2 decimales ";
	$DI_56_Catalogo  = "Neto no coincide con la directiva de calidad de la DGRH(9999999999.99)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[0-9]{8}.[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_56."|".$LocCampo."|" . $DI_56_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_56."|".$LocCampo."|" . $DI_56_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_56

/*************************************************************
* 
*  Funcion : fncValidaDI_57
*  Objetivo: Validar el campo Número de Trailers-Total  de Conceptos
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_57($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_57           = "(57)Número de Trailers-Total  de Conceptos ";
	$DI_57_ErrTam    = "Número de Trailers-Total  de Conceptos debe  ser de 2 ";
	$DI_57_Catalogo  = "No coincide con directiva de Calidad (Numérico a 2 posiciones)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS){
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_57."|".$LocCampo."|" . $DI_57_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_57."|".$LocCampo."|" . $DI_57_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_57


/*************************************************************
* 
*  Funcion : fncValidaDI_59
*  Objetivo: Validar el campo Nombre del Producto
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_59($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_58           = "(59)Nombre del Producto";
	$DI_58_ErrTam    = "Nombre del Producto debe  ser de 11 caracteres/numeros";
	$DI_58_Catalogo  = "No coincide con directiva de Calidad (Alfanumérico a 11)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[A-Z,a-z,0-9]{11}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_58."|".$LocCampo."|" . $DI_58_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_58."|".$LocCampo."|" . $DI_58_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_59



/*************************************************************
* 
*  Funcion : fncValidaDI_60
*  Objetivo: Validar el campo Número de Control 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_60($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_60           = "(60) Número de Control ";
	$DI_60_Catalogo  = "No coincide con directiva de Calidad (Numerico)";
	
	$LocCampo =$Campo;
	
	if(!preg_match("/[0-9]{6}/",$LocCampo))
	{
		$Error = $NumReg ."|".$DI_60."|".$LocCampo."|" . $DI_60_Catalogo."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}	
	return $Bandera;
} // fin de funcion fncValidaDI_60


/*************************************************************
* 
*  Funcion : fncValidaDI_61
*  Objetivo: Validar el campo Número de Cheque
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_61($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_61           = "(61)Número de Cheque";
	$DI_61_ErrTam    = "Número de Cheque debe  ser de 10 Digitos";
	$DI_61_Menor     = "Número de Cheque debe ser mayor a cero y numerico";
	$DI_61_Catalogo  = "No coincide con directiva de Calidad (Alfanumérico a 11)";

	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ){
		if($LocCampo <= CERO)
		{
			$Error = $NumReg ."|".$DI_61."|".$LocCampo."|" . $DI_61_Menor."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	

		if(!preg_match("/[0-9]{10}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_61."|".$LocCampo."|" . $DI_61_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_61."|".$LocCampo."|" . $DI_61_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_61


// no hay regla para el campo 62 Digito Verificador (Libre)


/*************************************************************
* 
*  Funcion : fncValidaDI_63 
*  Objetivo: Validar el campo Indicador de TESOFE-JORNADA
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_63($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_63           = "(63)Indicador de TESOFE -JORNADA";
	$DI_63_ErrTam    = "Indicador de TESOFE-JORNADA debe  ser de 2 Digitos";
	$DI_63_Catalogo  = "Indicador de TESOFE-JORNADA No coincide con catalogo definido por la DGRH";
	
	$JorArray =array("01","02","03","04","05");	

	$LocCampo = $Campo;
	if (strlen($LocCampo) == DOS){

		if(!in_array($LocCampo,$JorArray)){
			$Error = $NumReg ."|".$DI_63."|".$LocCampo."|" . $DI_63_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	

	}
	else{
		$Error = $NumReg ."|".$DI_63."|".$LocCampo."|" . $DI_63_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_63

/*************************************************************
* 
*  Funcion : fncValidaDI_65 
*  Objetivo: Validar el campo Ciclo del FONAC
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_65($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_65           = "(65)Ciclo del FONAC";
	$DI_65_ErrTam    = "Ciclo del FONAC debe  ser de 4 Digitos";
	$DI_65_DC  = "Ciclo del FONAC No coincide con la Directiva de Calidad definida por la DGRH(Numérico a 4 posiciones)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == CUATRO){


		if(!preg_match("/[0-9]{4}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_65."|".$LocCampo."|" . $DI_65_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_65."|".$LocCampo."|" . $DI_65_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_65

/*************************************************************
* 
*  Funcion : fncValidaDI_66
*  Objetivo: Validar el campo Número de Aportaciones al FONAC
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_66($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_66           = "(66)Número de Aportaciones al FONAC";
	$DI_66_ErrTam    = "Número de Aportaciones al FONAC debe  ser de 2 Digitos";
	$DI_66_DC  = "Número de Aportaciones al FONAC No coincide con la Directiva de Calidad definida por la DGRH(Numérico a 2 posiciones)";
	$DI_65_Catalogo  = "Número de Aportaciones al FONAC No coincide el catalogo definido por la DGRH(01-24)";
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == DOS){
		if(!preg_match("/[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_66."|".$LocCampo."|" . $DI_66_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if($LocCampo < 1 or $LocCampo > 24 ){
			$Error = $NumReg ."|".$DI_66."|".$LocCampo."|" . $DI_66_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_66."|".$LocCampo."|" . $DI_66_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_66

/*************************************************************
* 
*  Funcion : fncValidaDI_67
*  Objetivo: Validar el campo Acumulado de FONAC
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_67($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_67           = "(67)Acumulado de FONAC";
	$DI_67_ErrTam    = "Acumulado de FONAC debe  ser de 10 Digitos";
	$DI_67_DC  = "Acumulado de FONAC No coincide con la Directiva de Calidad definida por la DGRH(##########.##)";
	$DI_65_Catalogo  = "Acumulado de FONAC No coincide el catalogo definido por la DGRH(01-24)";
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == DIEZ){
		if(!preg_match("/[0-9]{7}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_67."|".$LocCampo."|" . $DI_67_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_67."|".$LocCampo."|" . $DI_67_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_67


/*************************************************************
* 
*  Funcion : fncValidaDI_68
*  Objetivo: Validar el campo Licencia sin Goce de Sueldo / CLUES
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_69($IdEstado, $GestorErr, $NumReg, $Campo){
	global $CLUES;	 
	$Bandera = CERO;
	$DI_69           = "(69)Licencia sin Goce de Sueldo / CLUES";
	$DI_69_ErrTam    = "Licencia sin Goce de Sueldo / CLUES  ser de 11 caracteres";
	$DI_69_DC  = "Licencia sin Goce de Sueldo / CLUES No coincide con la Directiva de Calidad definida por la DGRH";
	$DI_69_Catalogo  = "Licencia sin Goce de Sueldo / CLUES No coincide el catalogo definido por la DGRH";


		
	$LocCampo = $Campo;
	if (strlen($LocCampo) == 11){
		if(!in_array($LocCampo,$CLUES)){  
			$Error = $NumReg ."|".$DI_69."|".$LocCampo."|" . $DI_69_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_69."|".$LocCampo."|" . $DI_69_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_69


/*************************************************************
* 
*  Funcion : fncValidaDI_70
*  Objetivo: Validar el campo Porcentaje de Pensión 01 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_70($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_70           = "(70)Porcentaje de Pensión 01 ";
	$DI_70_ErrTam    = "Porcentaje de Pensión 01   ser de 3 enteros y 2 decimales(###.##)";
	$DI_70_DC  = "Porcentaje de Pensión 01  No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_70."|".$LocCampo."|" . $DI_70_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_70."|".$LocCampo."|" . $DI_70_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_70

/*************************************************************
* 
*  Funcion : fncValidaDI_71
*  Objetivo: Validar el campo Porcentaje de Pensión 01 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_71($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_71           = "(71)Porcentaje de Pensión 02 ";
	$DI_71_ErrTam    = "Porcentaje de Pensión 02   ser de 3 enteros y 2 decimales(###.##)";
	$DI_71_DC  = "Porcentaje de Pensión 02  No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_71."|".$LocCampo."|" . $DI_71_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_71."|".$LocCampo."|" . $DI_71_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_71

/*************************************************************
* 
*  Funcion : fncValidaDI_72
*  Objetivo: Validar el campo Porcentaje de Pensión 03
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_72($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_72           = "(72)Porcentaje de Pensión 03";
	$DI_72_ErrTam    = "Porcentaje de Pensión 03 ser de 3 enteros y 2 decimales(###.##)";
	$DI_72_DC  = "Porcentaje de Pensión 03 No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_72."|".$LocCampo."|" . $DI_72_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_72."|".$LocCampo."|" . $DI_72_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_72


/*************************************************************
* 
*  Funcion : fncValidaDI_73
*  Objetivo: Validar el campo Porcentaje de Pensión 04
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_73($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_73           = "(73)Porcentaje de Pensión 04";
	$DI_73_ErrTam    = "Porcentaje de Pensión 04 ser de 3 enteros y 2 decimales(###.##)";
	$DI_73_DC  = "Porcentaje de Pensión 04 No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_73."|".$LocCampo."|" . $DI_73_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_73."|".$LocCampo."|" . $DI_73_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_73


/*************************************************************
* 
*  Funcion : fncValidaDI_74
*  Objetivo: Validar el campo Porcentaje de Pensión 05
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_74($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_74           = "(74)Porcentaje de Pensión 05";
	$DI_74_ErrTam    = "Porcentaje de Pensión 04 ser de 3 enteros y 2 decimales(###.##)";
	$DI_74_DC  = "Porcentaje de Pensión 04 No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_74."|".$LocCampo."|" . $DI_74_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_74."|".$LocCampo."|" . $DI_74_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_74


/*************************************************************
* 
*  Funcion : fncValidaDI_75
*  Objetivo: Validar el campo Elección de tipo de retiro del ISSSTE
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_75($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_75           = "(75)Elección de tipo de retiro del ISSSTE";
	$DI_75_ErrTam    = "Elección de tipo de retiro del ISSSTE 1 enteros [0,1,2]";
	$DI_75_DC  = "Elección de tipo de retiro con la Directiva de Calidad definida por la DGRH[0 (sin descripción), 1 (decimo transitorio), 2 (cuenta individual)]";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == UNO){
		if(!preg_match("/[0-2]{1}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_75."|".$LocCampo."|" . $DI_75_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_75."|".$LocCampo."|" . $DI_75_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_75


/*************************************************************
* 
*  Funcion : fncValidaDI_76
*  Objetivo: Validar el campo Tipo de Unidad
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_76($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_76           = "(76)Tipo de Unidad";
	$DI_76_ErrTam    = "Tipo de Unidad 1 enteros [1,2]";
	$DI_76_DC  = "Tipo de Unidad con la Directiva de Calidad definida por la DGRH[1-2]";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == UNO){
		if(!preg_match("/[1-2]{1}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_76."|".$LocCampo."|" . $DI_76_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_76."|".$LocCampo."|" . $DI_76_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_76


/*************************************************************
* 
*  Funcion : fncValidaDI_77
*  Objetivo: Validar el campo Descripción de Centro de Responsabilidad
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_77($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_77           = "(77)Descripción de Centro de Responsabilidad";
	$DI_77_ErrTam    = "Descripción de Centro de Responsabilidad no cumple con el tamaño de 150 caracteres";
	$DI_77_DC  = "Descripción de Centro de Responsabilidad de Calidad definida por la DGRH";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= 150){
		if(!preg_match("/[0-9,A-Z,a-z,' ']/",$LocCampo)){
			$Error = $NumReg ."|".$DI_77."|".$LocCampo."|" . $DI_77_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_77."|".$LocCampo."|" . $DI_77_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_77



/*************************************************************
* 
*  Funcion : fncValidaDC1_15_21_EP
*  Objetivo: Validar la estructura programatica
*            
*  Fecha   : 29-Nov-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDC1_15_21_EP($IdEstado, $GestorErr, $NumReg, $Campo,$UR){
	global $ProductoNomina; 
	global $EPO, $EPC, $UREP;
	$Bandera      = CERO;
	$DC_1         = "(DC1)ESTRUCTURA PROGRAMATICA";
	$DC_1_ErrCatCan  = "E.P. Cancelados no cumple con la Directiva de Calidad definida por la DGRH";
	$DC_1_ErrCat  = "E.P. no cumple con la Directiva de Calidad definida por la DGRH";
	//echo "fncValidaDC1_15_21_EP/>". $Campo."< UR>".$UR."< <br>";
	//print_r($EPO) ;
	$LocCampo = $Campo;
	if(in_array($UR,$UREP)){
		if (preg_match("/7[0-9,A-Z,a-z]{1}/",$ProductoNomina)){
			if(!in_array($LocCampo,$EPC)){
				$Error = $NumReg ."|".$DC_1."|".$LocCampo."|" . $DC_1_ErrCatCan."|\n";
				fwrite($GestorErr, $Error);
				$Bandera = UNO;
			}	
		}
		else{
			if(!in_array($LocCampo,$EPO)){
				$Error = $NumReg ."|".$DC_1."|".$LocCampo."|" . $DC_1_ErrCat."|\n";
				fwrite($GestorErr, $Error);
				$Bandera = UNO;
			}	
		}
	}// fin del if(in_array($UR,$UREP))
	return $Bandera;
} // fin de funcion fncValidaDC1_15_21_EP



/*************************************************************
* 
*  Funcion : fncValidaDC2
*  Objetivo: Validar Producto de nomina Mencionados
*            
*  Fecha   : 29-Nov-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDC2($IdEstado, $GestorErr, $NumReg, $Campo){
	global $ProductoNomina; 
	
	$Bandera      = CERO;
	$DC_2         = "(DC2)PENSIONADOS";
	$DC_2_Pensionado  = "Tipo de Trabaajador no corresponde con producto de Nomina Cancelados";
	
	$LocCampo = $Campo;
	if (preg_match("/9[0-9,A-Z,a-z]{1}/",$ProductoNomina)){
		if ($LocCampo == "20"){
			$Bandera = CERO;
		}
		else{
				$Error = $NumReg ."|".$DC_2."|".$LocCampo."|" . $DC_2_Pensionado."|\n";
				fwrite($GestorErr, $Error);
				$Bandera = UNO;
		}
	}
	return $Bandera;
} // fin de funcion fncValidaDC2

/*************************************************************
* 
*  Funcion : fncValidaDC3
*  Objetivo: 
*            
*  Fecha   : 29-Nov-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   



/*************************************************************
* 
*  Funcion : fncValidaDC4
*  Objetivo: DIRECTIVA DE CALIDAD AÑO REAL
*            
*  Fecha   : 29-Nov-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   $PPAGOI   : Periodo de Pago Inicial
*   $PPAGOF   : Periodo de Pago Final
*   $QNAREAL  : Quincena de Proceso ó Real
*   $ANIOREAL : Año de Proceso ó Real
*
***************************************************************/   

function fncValidaDC4($IdEstado, $GestorErr, $NumReg, $PPAGOI,$PPAGOF, $QNAREAL, $ANIOREAL){
	global  $ProductoNomina, $AnioEnvio, $QnaEnvio; 
	
	$Bandera      = CERO;
	$DC_4         = "(DC4)ANIO REAL";
	$DC_4_AnioRealPNO  = "Anio y Qna Real diferentes a Anio y Qna Envio en PN Ordinaria";
	$DC_4_Periodos  = "Periodos de Pagoa Inicial y Final incorrectos";
	$DC_4_PeriodosPNO  = "Periodos de Pagoa Inicial y Final incorrectos PN>".$ProductoNomina;

	$Real  = $ANIOREAL.$QNAREAL;
	$Envio = $AnioEnvio . $QnaEnvio;

	$LocCampo = $Real."/".$Envio;

	if ($ProductoNomina == "11"){
		if ($Real != $Envio){
			$Error = $NumReg ."|".$DC_4."|".$LocCampo."|" . $DC_4_AnioRealPNO."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		else{
			$Periodos = $Periodo($QnaEnvio);
			$Periodo = $PPAGOI.$PPAGOF;

			if($Periodos!= $Periodo){
				$Error = $NumReg ."|".$DC_1."|".$PPAGOI."/".$PPAGOF."-".$Periodos."|" . $DC_4_Periodos."|\n";
				fwrite($GestorErr, $Error);
				$Bandera = UNO;
			}	
		}
	}
	else{
		if ($Real > $Envio){
			$Error = $NumReg ."|".$DC_4."|".$Real ."/".$Envio."|" . $DC_4_AnioRealPNO."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}

	return $Bandera;
} // fin de funcion fncValidaDC4


/*************************************************************
* 
*  Funcion : fncValidaDC6
*  Objetivo: 6.	DIRECTIVA DE CALIDAD PAGOS NOMINA ORDINARIA(DUP)
*            
*  Fecha   : 30-Nov-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   $GestorErr : Es controlador del archivo que controla los errores
*
***************************************************************/   

function fncValidaDC6($IdEstado, $GestorErr, $ArchivoDatos){
	global $ProductoNomina,$IdRemesa,$IdArchivoPN,$TagEnvio;	
	$db = new DbCnnx();   
	$Bandera      = CERO;
	$DC_6         = "(DC6)DUPLICADOS PAGOS NOMINA ORDINARIA";
	$DC_6_AnioRealPNO  = "Anio y Qna Real diferentes a Anio y Qna Envio en PN Ordinaria";
	$StrArchivo = "";
	$CMDCAT="";
	if($ProductoNomina=="11"){
			$COMMAND = "../mto/ordena_archivo.sh ".$ArchivoDatos;
			//echo "Comado >>".$COMMAND ."<<";
			// Conectarse a la base de datos 
			$SQL = "select archivo 
						from logger 
						where id_remesas=$IdRemesa  and 
						id_tipo_nom='11' and tipo_archivo='D'";
						// and estatus='K'
			//echo "fncValidaDC6/SQL >>"	.$SQL ."<< <br>";

			$Rows = $db->select($SQL);
			$Contador = CERO;
			while(isset($Rows[$Contador]['archivo'])){
					if($Contador == CERO)				
						$StrArchivo ="cat ";
					$StrArchivo = $StrArchivo . $Rows[$Contador]['archivo'] ." ";
					$Contador++;
			}// fin de while	

			if($Contador > CERO){
				$CMDCAT = $StrArchivo." ".$ArchivoDatos." > ../staging/".$TagEnvio."_".$IdArchivoPN;
			echo "CMDCAT >>".$CMDCAT ."< <BR>";				
				exec($CMDCAT);
				$COMMAND = "../mto/ordena_archivo.sh "."../staging/".$TagEnvio."_".$IdArchivoPN;
			}
			echo "COMANDO >>".$COMMAND ."< <BR>";			
			$Outpout = exec($COMMAND,$Salida);

			//echo "Salida >>".$Salida."<< <br>";
			//echo "Outpout >>".$Outpout."<< <br>";
			
			if(count($Salida) > CERO){
				foreach ($Salida as $Dup)
					fwrite($GestorErr,  $Dup."\n");
				$Bandera = UNO;
			}
	}
	return $Bandera;
} // fin de funcion fncValidaDC6



/*************************************************************
* 
*  Funcion : fncValidaDC8
*  Objetivo: 8.	DIRECTIVA DE CALIDAD CLUES
*            
*  Fecha   : 02-Dic-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   $GestorErr : Es controlador del archivo que controla los errores
*
***************************************************************/   

function fncValidaDC8($IdEstado, $GestorErr, $UR,$VALORCLUES){
	global $TagEnvio, $URA74,$CLUES;	
	$ArrTagEnvio = explode("-",$TagEnvio);
	$TipoArchivo = $ArrTagEnvio[CINCO];
	$Bandera      = CERO;
	$DC_8         = "(DC8) CLUES";
	$DC_8_CLUES  = "CLUES no corresponde con DC definida por la DGRH";

	if($TipoArchivo=="6" and in_array($UR, $URA74)){
		if(!in_array($VALORCLUES, $CLUES )){
			$Error = $NumReg ."|".$DC_8."|".$UR ."/".$VALORCLUES."|" . $DC_8_CLUES."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	return $Bandera;
} // fin de funcion fncValidaDC8

?>
