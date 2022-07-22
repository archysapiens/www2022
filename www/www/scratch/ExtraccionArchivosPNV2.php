<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '1024M');
ini_set('max_execution_time', 12000);
require('../general/generales.inc');
//require('../ptma_opcd/pfma_validacion_archivos.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');

$IndMando = array("01","08","10","30","50","60","70","75","80","90");


$sql = " select estado, QNAPROC,tipnom
	from bd4162016
	where QNAPROC='01'
	group by estado, QNAPROC, tipnom
	order by 1,2";

$res = $db->execFetchAll($sql, "pro_nomina");
$Contador =8;
$MSG=	"";
//$MSG=	"NO APLICA DE ACUERDO AL MANUAL DE PERCEPCIONES";
foreach ($res as $row) {
			//	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";

				//print_r ($row);
				$Estado =$row['ESTADO'];
				$QnaProc=$row['QNAPROC'];
				$TipNom =$row['TIPNOM'];
				echo "Estado |$Estado|TipNom|$TipNom <br>";
				
				if(!is_dir("./".$Estado))
					mkdir("./".$Estado);

				$GestorArchivo    = fopen("./".$Estado."/".$Estado."_".$QnaProc."_".$TipNom.".dat", "w");
				$GestorArchivoTra = fopen("./".$Estado."/".$Estado."_".$QnaProc."_".$TipNom.".tra", "w");

				if (!$GestorArchivo or !$GestorArchivoTra) {
					echo "Error al abrir archivo Error >>estructura.txt" ."<<";
				}
				else{
				$dbDet = new DbOracle("pro_nomina", "ArchiSoft");	



				if($Estado=='DF'){
					$sqlIN="select 
						NUEMP,RFC,CURP,NOMBRE , SAR,
						BANCOA,BANCON,NUMCTA,CLABE,CVESPC,CP,CALLE,COLONIA,DELEG,UR,GF,FN,SF,PG,
						AL,PP,PARTIDA,PUESTO,NUMPTO,EDO,MPIO,CR,CI,PAGADURI,AHISA,TABPTO,NIVEL,RANGO,INDMANDO,
						HORAS,PORCENT,TIPOTRAB,NIVELPTO,INDEMP,FIGF,FSSA,FREING,TIPOMOV,FPAGO,PPAGOI,PPAGOF,PQNAI,
						PQNAF,QNAREAL,ANIOREAL,TIPOPAGO,INSTRUA,INSTRUN,PER,DED,NETO,NOTRIAL,DIASLAB,NOMPROD,NUMCTROL,
						NUMCHEQ,DIGVER,TESOFE,DIASPD,CICLOF,NUMAPORT,ACUMF,FALTAS,to_char(LSGS) as LSGS ,PORPEN01,PORPEN02,PORPEN03,PORPEN04,
						PORPEN05,ISSSTE,TIPOUNI,CRESPDES,VERSION,ESTADO,TIPNOM,QNAPROC,ANIOPROC,QNAENVIO,ANIOENV,NOMARCH,TIPOPER,LLAVE
						from bdac2016
						where  estado='$Estado' and 
						qnaproc='$QnaProc' and 
						TIPNOM='$TipNom' 

						union 

						select 
						NUEMP,RFC,CURP,NOMBRE , SAR,
						BANCOA,BANCON,NUMCTA,CLABE,FUNCION as CVESPC,CP,CALLE,COLONIA,DELEG,UR,GF,FN,SF,PG,
						AL,PP,PARTIDA,PUESTO,NUMPTO,EDO,MPIO,CR,CI,PAGADURI,FINANCIAMIENTO as AHISA,TABPTO,NIVEL,RANGO,INDMANDO,
						HORAS,PORCENT,TIPOTRAB,NIVELPTO,INDEMP,FIGF,FSSA,FREING,TIPOMOV,FPAGO,PPAGOI,PPAGOF,PQNAI,
						PQNAF,QNAREAL,ANIOREAL,TIPOPAGO,INSTRUA,INSTRUN,PER,DED,NETO,NOTRIAL,DIASLAB,NOMPROD,NUMCTROL,
						NUMCHEQ,DIGVER,JORNADA as TESOFE,DIASPD,CICLOF,NUMAPORT,ACUMF,FALTAS, CLUES as LSGS ,PORPEN01,PORPEN02,PORPEN03,PORPEN04,
						PORPEN05,ISSSTE,TIPOUNI,CRESPDES,VERSION,ESTADO,TIPNOM,QNAPROC,ANIOPROC,QNAENVIO,ANIOENV,NOMARCH,TIPOPER,LLAVE
						from bd4162016
						where  estado='$Estado' and 
						qnaproc='$QnaProc' and 
						TIPNOM='$TipNom'";
				}		
				else{
				 $sqlIN = "						select 
						NUEMP,RFC,CURP,NOMBRE , SAR,
						BANCOA,BANCON,NUMCTA,CLABE,FUNCION as CVESPC,CP,CALLE,COLONIA,DELEG,UR,GF,FN,SF,PG,
						AL,PP,PARTIDA,PUESTO,NUMPTO,EDO,MPIO,CR,CI,PAGADURI,FINANCIAMIENTO as AHISA,TABPTO,NIVEL,RANGO,INDMANDO,
						HORAS,PORCENT,TIPOTRAB,NIVELPTO,INDEMP,FIGF,FSSA,FREING,TIPOMOV,FPAGO,PPAGOI,PPAGOF,PQNAI,
						PQNAF,QNAREAL,ANIOREAL,TIPOPAGO,INSTRUA,INSTRUN,PER,DED,NETO,NOTRIAL,DIASLAB,NOMPROD,NUMCTROL,
						NUMCHEQ,DIGVER,JORNADA as TESOFE,DIASPD,CICLOF,NUMAPORT,ACUMF,FALTAS, CLUES as LSGS ,PORPEN01,PORPEN02,PORPEN03,PORPEN04,
						PORPEN05,ISSSTE,TIPOUNI,CRESPDES,VERSION,ESTADO,TIPNOM,QNAPROC,ANIOPROC,QNAENVIO,ANIOENV,NOMARCH,TIPOPER,LLAVE
						from bd4162016
						where  estado='$Estado' and 
						qnaproc='$QnaProc' and 
						TIPNOM='$TipNom'";
				}				

	        	$resDet = $dbDet->execFetchAll($sqlIN, "Query Example");
			       
		        foreach ($resDet as $rowDet) {
				        
		        	    $Nuemp = $rowDet['NUEMP'];
						$Rfc = $rowDet['RFC'];

						$Curp = $rowDet['CURP'];
						$Nombre = $rowDet['NOMBRE'];
						if(!preg_match ("/[&,?,A-Z,a-z,\s]{1,90},[&,?,A-Z,a-z,\s]{1,90}\/[&,?.A-Z,a-z,\s]{1,90}/" ,$Nombre))
							$Nombre="Lerdorf,PHP/Rasmus";
						

						$Sar = $rowDet['SAR'];
						$Bancoa = $rowDet['BANCOA'];
						$Bancon = "37006";
						if ($Bancon < 5)
							$Bancon = "90600";

						$Numcta = $rowDet['NUMCTA'];
						$Numcta = str_pad($Numcta, 16,"0",STR_PAD_LEFT);						

						$Clabe = $rowDet['CLABE'] ;

						$Clabe = str_pad($Clabe, 18,"0",STR_PAD_LEFT);
						$Clabe = substr($Clabe, 0,18);

						$Cvespc = $rowDet['CVESPC'];
						$Cvespc= str_pad($Cvespc, 2,"0",STR_PAD_LEFT);

						$Cp = $rowDet['CP'];
						$Calle = $rowDet['CALLE'];
						$Colonia = $rowDet['COLONIA'];
						$Deleg = $rowDet['DELEG'];
						$Ur = $rowDet['UR'];
						$Gf = $rowDet['GF'];
						$Fn = $rowDet['FN'];
						$Sf = $rowDet['SF'];
						$Pg = "04"; //$rowDet['PG'];
						$Al = $rowDet['AL'];
						$Pp = $rowDet['PP'];
						$Partida = $rowDet['PARTIDA'];
						$Puesto = "OP98542";  //$rowDet['PUESTO'];
						$Numpto = "0022";     // $rowDet['NUMPTO'];
						$Edo = $rowDet['EDO'];
						$Mpio = $rowDet['MPIO'];
						$Cr = $rowDet['CR'];
						$TmpEdo =$rowDet['ESTADO'];
						$ArrTmpEdo =array($TmpEdo);

						if (strlen($Cr) == DIEZ)
						{
							if(!in_array(substr($Cr,0,2),$ArrTmpEdo))
								$Cr = $TmpEdo."00000001";
							if(!preg_match("/\d{8}/",substr($Cr,2,8)))
								$Cr = $TmpEdo."00000001";
						}
						else
							$Cr = $TmpEdo."00000001";
						

						$Ci = "80012345678"; // $rowDet['CI'];


						$Pagaduri = $rowDet['PAGADURI'];
						$Ahisa = $rowDet['AHISA'];
						$Ahisa = str_pad($Ahisa, 2,"0",STR_PAD_LEFT);


						$Tabpto = $rowDet['TABPTO'];
						$Nivel = $rowDet['NIVEL'];
						$Rango = $rowDet['RANGO']; // ****

						$Indmando = $rowDet['INDMANDO'];
						if(!in_array($Indmando, $IndMando))
								$Indmando="01";
						

						$Horas = $rowDet['HORAS'];
						if ($Horas <= CERO)
							$Horas=1;
						

						$Porcent = $rowDet['PORCENT'];
						$Tipotrab = $rowDet['TIPOTRAB'];
						$Nivelpto = "0123456789"; //$rowDet['NIVELPTO'];

						$Indemp = $rowDet['INDEMP'];

						$Figf = $rowDet['FIGF'];
						if (trim(strlen($Figf)) < 8)
							$Figf = "20160919";

						$Fssa = $rowDet['FSSA'];
						if (trim(strlen($Fssa)) < 8)
							$Fssa = "20160920";

						$Freing = $rowDet['FREING'];
						if (trim(strlen($Freing)) < 8)
							$Freing = "20160921";



						$Tipomov = $rowDet['TIPOMOV'];
						$Fpago = $rowDet['FPAGO'];
						if (trim($Fpago) == "" OR strlen(trim($Fpago)) < NUEVE)
							$Fpago="01ENE2016";

						$Ppagoi = $rowDet['PPAGOI'];
						$Ppagof = $rowDet['PPAGOF'];

						$Pqnai = "20160901"; //$rowDet['PQNAI'];
						$Pqnaf = "20160915"; //$rowDet['PQNAF'];

						$Qnareal = $rowDet['QNAREAL'];
						$Anioreal = $rowDet['ANIOREAL'];
						$Tipopago = $rowDet['TIPOPAGO'];
						$Instrua = $rowDet['INSTRUA'];
						$Instrun = $rowDet['INSTRUN'];
						if ($Instrun <= CERO)
							$Instrun="02";

						$Per = "12345678.00";  //$rowDet['PER'];
						$Ded = "12345678.00"; //$rowDet['DED'];
						$Neto = "12345678.00"; //$rowDet['NETO'];

						$Notrial = $rowDet['NOTRIAL'];
						$Notrial = str_pad($Notrial, 2,"0",STR_PAD_LEFT);


						$Diaslab = $rowDet['DIASLAB'];
						$Nomprod = $rowDet['NOMPROD'];
						$Nomprod = str_pad($Nomprod, 11,"0",STR_PAD_LEFT);

						$Numctrol = $rowDet['NUMCTROL'];
						$Numctrol = str_pad($Numctrol, 6,"0",STR_PAD_LEFT);

						$Numcheq = $rowDet['NUMCHEQ'];
						$Numcheq = str_pad($Numcheq, 10,"0",STR_PAD_LEFT);

						$Digver = $rowDet['DIGVER'];
						$Tesofe = "01"; //$rowDet['TESOFE'];

						$Diaspd = $rowDet['DIASPD'];

						$Ciclof = "1234"; //$rowDet['CICLOF'];


						$Numaport = $rowDet['NUMAPORT'];
						if ($Numaport <= CERO)
							$Numaport="01";
						else		
							$Numaport = str_pad($Numaport, 2,"0",STR_PAD_LEFT);

						$Acumf = "1234567.00"; // $rowDet['ACUMF'];


						$Faltas = $rowDet['FALTAS'];
						$Lsgs = $rowDet['LSGS'];

						$IdEstado = $rowDet['ESTADO'];
						$Clues="";

						if($IdEstado == "01"){
							$Clues = "ASSSA000013";
						} //fin de if($IdEstado == "01")

						//Condicion de estado-clues
						if($IdEstado == "02"){
							$Clues = "BCSSA000015";
						} //fin de if($IdEstado == "02")

						//Condicion de estado-clues
						if($IdEstado == "03"){
							$Clues = "BSSSA000011";
						} //fin de if($IdEstado == "03")

						//Condicion de estado-clues
						if($IdEstado == "04"){
							$Clues = "CCSSA000025";
						} //fin de if($IdEstado == "04")

						//Condicion de estado-clues
						if($IdEstado == "05"){
							$Clues = "CLSSA000016";
						} //fin de if($IdEstado == "05")

						//Condicion de estado-clues
						if($IdEstado == "06"){
							$Clues = "CMSSA000014";
						} //fin de if($IdEstado == "06")

						//Condicion de estado-clues
						if($IdEstado == "07"){
							$Clues = "CSSSA000016";
						} //fin de if($IdEstado == "07")

						//Condicion de estado-clues
						if($IdEstado == "08"){
							$Clues = "CHSSA000022";
						} //fin de if($IdEstado == "08")

						//Condicion de estado-clues
						if($IdEstado == "09"){
							$Clues = "DFSSA000053";
						} //fin de if($IdEstado == "09")

						//Condicion de estado-clues
						if($IdEstado == "10"){
							$Clues = "DGSSA000010";
						} //fin de if($IdEstado == "10")

						//Condicion de estado-clues
						if($IdEstado == "11"){
							$Clues = "GTSSA000013";
						} //fin de if($IdEstado == "11")

						//Condicion de estado-clues
						if($IdEstado == "12"){
							$Clues = "GRSSA000010";
						} //fin de if($IdEstado == "12")

						//Condicion de estado-clues
						if($IdEstado == "13"){
							$Clues = "HGSSA000016";
						} //fin de if($IdEstado == "13")

						//Condicion de estado-clues
						if($IdEstado == "14"){
							$Clues = "JCSSA000013";
						} //fin de if($IdEstado == "14")

						//Condicion de estado-clues
						if($IdEstado == "15"){
							$Clues = "MCSSA000014";
						} //fin de if($IdEstado == "15")

						//Condicion de estado-clues
						if($IdEstado == "16"){
							$Clues = "MNSSA000013";
						} //fin de if($IdEstado == "16")

						//Condicion de estado-clues
						if($IdEstado == "17"){
							$Clues = "MSSSA000022";
						} //fin de if($IdEstado == "17")

						//Condicion de estado-clues
						if($IdEstado == "18"){
							$Clues = "NTSSA000013";
						} //fin de if($IdEstado == "18")

						//Condicion de estado-clues
						if($IdEstado == "19"){
							$Clues = "NLSSA000015";
						} //fin de if($IdEstado == "19")

						//Condicion de estado-clues
						if($IdEstado == "20"){
							$Clues = "OCSSA000010";
						} //fin de if($IdEstado == "20")

						//Condicion de estado-clues
						if($IdEstado == "21"){
							$Clues = "PLSSA000011";
						} //fin de if($IdEstado == "21")

						//Condicion de estado-clues
						if($IdEstado == "22"){
							$Clues = "QTSSA000014";
						} //fin de if($IdEstado == "22")

						//Condicion de estado-clues
						if($IdEstado == "23"){
							$Clues = "QRSSA000011";
						} //fin de if($IdEstado == "23")

						//Condicion de estado-clues
						if($IdEstado == "24"){
							$Clues = "SPSSA000011";
						} //fin de if($IdEstado == "24")

						//Condicion de estado-clues
						if($IdEstado == "25"){
							$Clues = "SLSSA000024";
						} //fin de if($IdEstado == "25")

						//Condicion de estado-clues
						if($IdEstado == "26"){
							$Clues = "SRSSA000014";
						} //fin de if($IdEstado == "26")

						//Condicion de estado-clues
						if($IdEstado == "27"){
							$Clues = "TCSSA000014";
						} //fin de if($IdEstado == "27")

						//Condicion de estado-clues
						if($IdEstado == "28"){
							$Clues = "TSSSA000010";
						} //fin de if($IdEstado == "28")

						//Condicion de estado-clues
						if($IdEstado == "29"){
							$Clues = "TLSSA000010";
						} //fin de if($IdEstado == "29")

						//Condicion de estado-clues
						if($IdEstado == "30"){
							$Clues = "VZSSA000013";
						} //fin de if($IdEstado == "30")

						//Condicion de estado-clues
						if($IdEstado == "31"){
							$Clues = "YNSSA000022";
						} //fin de if($IdEstado == "31")

						$Lsgs = $Clues;

						$Porpen01 = "123.00";   //$rowDet['PORPEN01'];
						$Porpen02 = "123.00";   //$rowDet['PORPEN02'];
						$Porpen03 = "123.00";   // $rowDet['PORPEN03'];
						$Porpen04 = "123.00";   //$rowDet['PORPEN04'];
						$Porpen05 = "123.00";   //$rowDet['PORPEN05'];

						$Issste    = $rowDet['ISSSTE'];
						$Tipouni   = $rowDet['TIPOUNI'];
						$Crespdes  = $rowDet['CRESPDES'];
/**						
						$Version   = $rowDet['VERSION'];
						$Estado    = $rowDet['ESTADO'];
						$Tipnom    = $rowDet['TIPNOM'];
						$Qnaproc   = '19';    //$rowDet['QNAPROC'];
						$Anioproc  = $rowDet['ANIOPROC'];
						$Qnaenvio  = '19';    //$rowDet['QNAENVIO'];
						$Anioenv   = $rowDet['ANIOENV'];
						$Nomarch   = $rowDet['NOMARCH'];
						$Tipoper   = $rowDet['TIPOPER'];
						
**/
$Llave     = $rowDet['LLAVE'];
						$StrOut=    $Nuemp."|".
									$Rfc.'|'.
									$Curp.'|'.
									$Nombre.'|'.
									$Sar.'|'.
									$Bancoa.'|'.
									$Bancon.'|'.
									$Numcta.'|'.
									$Clabe.'|'.
									$Cvespc.'|'.
									$Cp.'|'.
									$Calle.'|'.
									$Colonia.'|'.
									$Deleg.'|'.
									$Ur.'|'.
									$Gf.'|'.
									$Fn.'|'.
									$Sf.'|'.
									$Pg.'|'.
									$Al.'|'.
									$Pp.'|'.
									$Partida.'|'.
									$Puesto.'|'.
									$Numpto.'|'.
									$Edo.'|'.
									$Mpio.'|'.
									$Cr.'|'.
									$Ci.'|'.
									$Pagaduri.'|'.
									$Ahisa.'|'.
									$Tabpto.'|'.
									$Nivel.'|'.
									$Rango.'|'.
									$Indmando.'|'.
									$Horas.'|'.
									$Porcent.'|'.
									$Tipotrab.'|'.
									$Nivelpto.'|'.
									$Indemp.'|'.
									$Figf.'|'.
									$Fssa.'|'.
									$Freing.'|'.
									$Tipomov.'|'.
									$Fpago.'|'.
									$Ppagoi.'|'.
									$Ppagof.'|'.
									$Pqnai.'|'.
									$Pqnaf.'|'.
									$Qnareal.'|'.
									$Anioreal.'|'.
									$Tipopago.'|'.
									$Instrua.'|'.
									$Instrun.'|'.
									$Per.'|'.
									$Ded.'|'.
									$Neto.'|'.
									$Notrial.'|'.
									$Diaslab.'|'.
									$Nomprod.'|'.
									$Numctrol.'|'.
									$Numcheq.'|'.
									$Digver.'|'.
									$Tesofe.'|'.
									$Diaspd.'|'.
									$Ciclof.'|'.
									$Numaport.'|'.
									$Acumf.'|'.
									$Faltas.'|'.
									$Lsgs.'|'.
									$Porpen01.'|'.
									$Porpen02.'|'.
									$Porpen03.'|'.
									$Porpen04.'|'.
									$Porpen05.'|'.
									$Issste.'|'.
									$Tipouni.'|'.
									$Crespdes.'|'."\n";
/**
									$Version.'|'.
									$Estado.'|'.
									$Tipnom.'|'.
									$Qnaproc.'|'.
									$Anioproc.'|'.
									$Qnaenvio.'|'.
									$Anioenv.'|'.
									$Nomarch.'|'.
									$Tipoper.'|'.
									$Llave.'|' ."\n";
**/									

					fwrite($GestorArchivo, $StrOut);

					$dbTra = new DbOracle("pro_nomina", "ArchiSoft");	
					$SQLTRAIL ="select RFC, NUMEMP, NUMCHEQ, 
								TCONCEP, CONCEP, IMPORTE, ANIO, QNA, 
								PTAANT, TOTPAGOS, PAGOEFEC, NOMPROD, NUMCTROL, 
								NOMARCH, LLAVE
								from btac2016
								where llave='$Llave'  
								union  
								select RFC, NUMEMP, NUMCHEQ, 
								TCONCEP, CONCEP, IMPORTE, ANIO, QNA, 
								PTAANT, TOTPAGOS, PAGOEFEC, NOMPROD, NUMCTROL, 
								NOMARCH, LLAVE
								from bt4162016
								where llave='$Llave' ";

					//echo " SQLTRAIL >>$SQLTRAIL<< <br>";			

		        	$resTra = $dbTra->execFetchAll($SQLTRAIL, "Query Example");
				       
			        foreach ($resTra as $rowTra) {

						$Rfc = $rowTra['RFC'];
						$Numemp = $rowTra['NUMEMP'];
						$Numcheq = $rowTra['NUMCHEQ'];
						$Tconcep = $rowTra['TCONCEP'];
						$Concep = $rowTra['CONCEP'];
						$Importe = $rowTra['IMPORTE'];
						$Anio = $rowTra['ANIO'];
						$Qna = $rowTra['QNA'];
						$Ptaant = $rowTra['PTAANT'];
						$Totpagos = $rowTra['TOTPAGOS'];
						$Pagoefec = $rowTra['PAGOEFEC'];
						$Nomprod = $rowTra['NOMPROD'];
						$Numctrol = $rowTra['NUMCTROL'];
/**						
						$Nomarch = $rowTra['NOMARCH'];
						$Llave = $rowTra['LLAVE'];
**/
						$StrTra=$Rfc.'|'.
						$Numemp.'|'.
						$Numcheq.'|'.
						$Tconcep.'|'.
						$Concep.'|'.
						$Importe.'|'.
						$Anio.'|'.
						$Qna.'|'.
						$Ptaant.'|'.
						$Totpagos.'|'.
						$Pagoefec.'|'.
						$Nomprod.'|'.
						$Numctrol.'|'."\n";
/**						
						$Nomarch.'|'.
						$Llave.'|'."\n";
**/
						fwrite($GestorArchivoTra, $StrTra);
				
					}// fin foreach


		        }	// fin foreach
		        fclose($GestorArchivo);
		        fclose($GestorArchivoTra);
		}//fin del if de apertuta 	archivo
				$Contador++;
/**				
		if ($Contador >30)		
			break;

**/

}	// fin del for reach

?>		        