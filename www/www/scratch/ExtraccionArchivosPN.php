<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '1024M');
ini_set('max_execution_time', 12000);
require('../general/generales.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");

error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');




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
				
				if(!is_dir("./".$Estado))
					mkdir("./".$Estado);

				$GestorArchivo = fopen("./".$Estado."/".$Estado."_".$QnaProc."_".$TipNom.".txt", "w");
				if (!$GestorArchivo) 	{
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
						$Sar = $rowDet['SAR'];
						$Bancoa = $rowDet['BANCOA'];
						$Bancon = $rowDet['BANCON'];
						$Numcta = $rowDet['NUMCTA'];
						$Clabe = $rowDet['CLABE'];
						$Cvespc = $rowDet['CVESPC'];
						$Cp = $rowDet['CP'];
						$Calle = $rowDet['CALLE'];
						$Colonia = $rowDet['COLONIA'];
						$Deleg = $rowDet['DELEG'];
						$Ur = $rowDet['UR'];
						$Gf = $rowDet['GF'];
						$Fn = $rowDet['FN'];
						$Sf = $rowDet['SF'];
						$Pg = $rowDet['PG'];
						$Al = $rowDet['AL'];
						$Pp = $rowDet['PP'];
						$Partida = $rowDet['PARTIDA'];
						$Puesto = $rowDet['PUESTO'];
						$Numpto = $rowDet['NUMPTO'];
						$Edo = $rowDet['EDO'];
						$Mpio = $rowDet['MPIO'];
						$Cr = $rowDet['CR'];
						$Ci = $rowDet['CI'];
						$Pagaduri = $rowDet['PAGADURI'];
						$Ahisa = $rowDet['AHISA'];
						$Tabpto = $rowDet['TABPTO'];
						$Nivel = $rowDet['NIVEL'];
						$Rango = $rowDet['RANGO'];
						$Indmando = $rowDet['INDMANDO'];
						$Horas = $rowDet['HORAS'];
						$Porcent = $rowDet['PORCENT'];
						$Tipotrab = $rowDet['TIPOTRAB'];
						$Nivelpto = $rowDet['NIVELPTO'];
						$Indemp = $rowDet['INDEMP'];
						$Figf = $rowDet['FIGF'];
						$Fssa = $rowDet['FSSA'];
						$Freing = $rowDet['FREING'];
						$Tipomov = $rowDet['TIPOMOV'];
						$Fpago = $rowDet['FPAGO'];
						$Ppagoi = $rowDet['PPAGOI'];
						$Ppagof = $rowDet['PPAGOF'];
						$Pqnai = $rowDet['PQNAI'];
						$Pqnaf = $rowDet['PQNAF'];
						$Qnareal = $rowDet['QNAREAL'];
						$Anioreal = $rowDet['ANIOREAL'];
						$Tipopago = $rowDet['TIPOPAGO'];
						$Instrua = $rowDet['INSTRUA'];
						$Instrun = $rowDet['INSTRUN'];
						$Per = $rowDet['PER'];
						$Ded = $rowDet['DED'];
						$Neto = $rowDet['NETO'];
						$Notrial = $rowDet['NOTRIAL'];
						$Diaslab = $rowDet['DIASLAB'];
						$Nomprod = $rowDet['NOMPROD'];
						$Numctrol = $rowDet['NUMCTROL'];
						$Numcheq = $rowDet['NUMCHEQ'];
						$Digver = $rowDet['DIGVER'];
						$Tesofe = $rowDet['TESOFE'];
						$Diaspd = $rowDet['DIASPD'];
						$Ciclof = $rowDet['CICLOF'];
						$Numaport = $rowDet['NUMAPORT'];
						$Acumf = $rowDet['ACUMF'];
						$Faltas = $rowDet['FALTAS'];
						$Lsgs = $rowDet['LSGS'];
						$Porpen01 = $rowDet['PORPEN01'];
						$Porpen02 = $rowDet['PORPEN02'];
						$Porpen03 = $rowDet['PORPEN03'];
						$Porpen04 = $rowDet['PORPEN04'];
						$Porpen05 = $rowDet['PORPEN05'];
						$Issste = $rowDet['ISSSTE'];
						$Tipouni = $rowDet['TIPOUNI'];
						$Crespdes = $rowDet['CRESPDES'];
						$Version = $rowDet['VERSION'];
						$Estado = $rowDet['ESTADO'];
						$Tipnom = $rowDet['TIPNOM'];
						$Qnaproc = '19'; //$rowDet['QNAPROC'];
						$Anioproc = $rowDet['ANIOPROC'];
						$Qnaenvio = '19'; //$rowDet['QNAENVIO'];
						$Anioenv = $rowDet['ANIOENV'];
						$Nomarch = $rowDet['NOMARCH'];
						$Tipoper = $rowDet['TIPOPER'];
						$Llave = $rowDet['LLAVE'];

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
									$Crespdes.'|'.
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

					fwrite($GestorArchivo, $StrOut);

		        }	// fin foreach
		        fclose($GestorArchivo);
		}//fin del if de apertuta 	archivo
				$Contador++;
/**				
		if ($Contador >30)		
			break;

**/

}	// fin del for reach

?>		        