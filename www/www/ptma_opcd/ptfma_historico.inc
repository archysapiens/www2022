<?php

/*********************************************************************
 * 
 * Funcion : obtenerHistoricoQnas
 * Objetivo: Mostrar las quincenas pasadas, datos totales 
 *           y generales
 * Parametros
 * $QnaUrl:  Quincena actual y que limita el historico
 * $AnioUrl: Anio de la quincena referencia
 **********************************************************************/

function obtenerHistoricoQnas($QnaUrl, $AnioUrl){

 //print_r($_SESSION);

 $IdEstado = $_SESSION['idorg'];
 $Configuracion = $_SESSION['configuracion'];

 $ArrConf = explode("|", $Configuracion);
 $ArrProdNom =explode("@", $ArrConf[CUATRO]); 
 $TipoArch   = $ArrProdNom[CERO];

$IdRemesaTot = CERO;
$TotPer = CERO;
$TotDed = CERO;
$IdRemesaTotUR = CERO;
$TotPerUR = CERO;
$TotDedUR = CERO;


$HeaderRow = "  <!-- Inicio de row -->
                <div class=\"row animated fadeIn\">";
$TailRow   = "    </div>
                  <!-- Fin de row -->";  
$Body="";                             

$db = new DbCnnx();    	
$SQLHistorico = "SELECT   anio, numero, fecha_envio
				FROM periodos
				where numero <=".$QnaUrl . " and  anio = ".  $AnioUrl;
//echo "SQLHistorico >$SQLHistorico< <br>";
$rows = $db->select($SQLHistorico);

if(!is_array($rows)){
    $HistoricoQnas="X";
}    
else{
        $Contador = CERO;
        while(isset($rows[$Contador]['anio']))
        {
            $Anio = $rows[$Contador]['anio'];
            $NumQna = $rows[$Contador]['numero'];
            $FecLim = $rows[$Contador]['fecha_envio'];
            $Contador++;
            // se verifica el esatus de la Ultima carga 
            $Configuracion  = configuraSesion($NumQna,$Anio);
            
            $DatosConfig = explode("|", $Configuracion);
            //echo "<br>";
            //print_r ($DatosConfig);
            //echo "<br>";
            $TotalCampos = count($DatosConfig)-UNO;
            for($IndTipoArch = UNO; $IndTipoArch < $TotalCampos;$IndTipoArch++){
                    $DatosCarga= explode("@",$DatosConfig[$IndTipoArch]);
                    //echo "Dentro del for <br>";
                    //print_r ($DatosCarga);
                    $TipoCarga      = $DatosCarga[CERO];
                    $DescCarga      = $DatosCarga[UNO];
                    $EstatusCarga   = $DatosCarga[DOS];
                    $FechaCarga     = $DatosCarga[TRES];

            }// fin del for    
            if($NumQna==$QnaUrl){
                $Icono ="fa fa-clock-o fa-5x";
                $PanelColor ="panel-success";
            }    
            elseif($EstatusCarga!="" or $EstatusCarga!="E"){
                $Icono ="fa fa-exclamation-triangle fa-5x";
                $PanelColor ="panel-warning";
            }else{
                $Icono ="fa fa-server fa-5x";
                $PanelColor ="panel-primary";                
            }// fin del if    

            $SQLTotales = "Select lc.id_remesas, sum(percepciones) as per, 
                                    sum(deducciones) as ded
                            from remesas rem, log_carga lc
                            where rem.id= lc.id_remesas and 
                            rem.id_organismos='$IdEstado' and 
                            rem.anio_periodos=$Anio and 
                            rem.numero_periodos=$NumQna 
                            group by lc.id_remesas";
/**
and 
                            rem.id_archivos=$TipoArch
**/                            


             $dbTotales = new DbCnnx();           
             $rowTotales = $dbTotales->select($SQLTotales);
             $ContadorTot=CERO;
             $TotPer=CERO;
             $TotDed=CERO;
             while(isset($rowTotales[$ContadorTot]['id_remesas'])) {            
                    $IdRemesaTot = $rowTotales[$ContadorTot]['id_remesas'];
                    $TotPer += $rowTotales[$ContadorTot]['per'];
                    $TotDed += $rowTotales[$ContadorTot]['ded'];

                    $ContadorTot++;
             } // find el while  


            //echo "obtenerHistoricoQnas / SQLTotales >>$SQLTotales<< <br>";

             $TotalQuincena = $TotPer - $TotDed;

             $TotPerFmto = number_format($TotPer,2, '.',',');
             $TotDedFmto = number_format($TotDed,2, '.',',');
             $TotalQuincenaFmto = number_format($TotalQuincena,2, '.',',');            

               $SQLTotalesUR = "Select lc.ur, sum(lc.percepciones) as per, 
                                    sum(lc.deducciones) as ded
                            from log_carga lc
                            where lc.id_remesas=$IdRemesaTot 
                            group by lc.ur";
             $dbTotalesUR = new DbCnnx();           
             $rowTotalesUR = $dbTotalesUR->select($SQLTotalesUR);
             $ContadorTotUR=CERO;
             $BodyModal =""; 
             $TotPerUR = CERO;
             $TotDedUR = CERO;
             $TotPerURTotal =CERO;
             $TotPerURFmto = "";
             $TotDedURFmto = "";
             $TotPerURTotalFmto = "";
             $BodyModal =""; 
             while(isset($rowTotalesUR[$ContadorTotUR]['ur'])) {            
                    $IdRemesaTotUR = $rowTotalesUR[$ContadorTotUR]['ur'];
                    $TotPerUR = $rowTotalesUR[$ContadorTotUR]['per'];
                    $TotDedUR = $rowTotalesUR[$ContadorTotUR]['ded'];

                    $TotPerURTotal = $TotPerUR - $TotDedUR;

                    $TotPerURFmto = number_format($TotPerUR,2, '.',',');
                    $TotDedURFmto = number_format($TotDedUR,2, '.',',');
                    $TotPerURTotalFmto = number_format($TotPerURTotal,2, '.',',');

                    $BodyModal .= "
                              <div class=\"forum-item active\">
                                <div class=\"row\">
                                    <div class=\"col-md-6\">
                                        <div class=\"forum-icon\">
                                            <i class=\"fa  fa-user-md\"></i>
                                        </div>
                                        <a href=\"#\" class=\"forum-item-title\">Nómina tipo $IdRemesaTotUR</a>
                                        <div class=\"forum-sub-title\">
                                        
                                        </div>
                                    </div>

                                    <div class=\"col-md-2 forum-info\">
                                        <span class=\"forum-item-title\">
                                            $TotPerURTotalFmto
                                        </span>
                                        <div>
                                            <small>Total</small>
                                        </div>
                                    </div>
                                    <div class=\"col-md-2 forum-info\">
                                        <span class=\"forum-item-title\">
                                            $TotPerURFmto
                                        </span>
                                        <div>
                                            <small>Ingresos</small>
                                        </div>
                                    </div>
                                    <div class=\"col-md-2 forum-info\">
                                        <span class=\"forum-item-title\">
                                            $TotDedURFmto
                                        </span>
                                        <div>
                                            <small>Egresos</small>
                                        </div>
                                    </div>

                                </div>
                            </div>                         ";

                    $ContadorTotUR++;
             } // find el while  


             if($TotalQuincenaFmto <=CERO)
                 $BodyModal="";

            $Body .= "<div class=\"col-md-4\">
                    <div class=\"panel $PanelColor\">
                        <div class=\"panel-heading\">
                            <div class=\"row\">
                                <div class=\"col-xs-3\">
                                    <i class=\"$Icono\"></i>
                                </div>
                                <div class=\"col-xs-9 text-right\">
                                    <div class=\"huge\">QUINCENA $NumQna </div>
                                    <div>
                                    Percepciones: $ $TotPerFmto    </div>
                                    <div>Deducciones: $ $TotDedFmto</div>
                                    <div> Total : $ $TotalQuincenaFmto  </div>

                                </div>
                            </div>
                        </div>
                        <a href=\"#$Anio$NumQna\"  data-toggle=\"modal\" data-target=\"#$Anio$NumQna\">
                            <div class=\"panel-footer\">
                                <span class=\"pull-left\">Ver Detalles</span>
                                <span class=\"pull-right\">
                                <i class=\"fa fa-arrow-circle-right\"></i></span>
                                <div class=\"clearfix\"></div>
                            </div>
                        </a>

<!-- inicio del modal -->


                    <div class=\"modal inmodal\" id=\"$Anio$NumQna\" tabindex=\"-1\" role=\"dialog\" aria-hidden=\"true\">
                                <div class=\"modal-dialog\">
                                    <div class=\"modal-content animated flipInY\">

                                        <div class=\"modal-header\">
                                            <button type=\"button\" class=\"close\" data-dismiss=\"modal\"><span aria-hidden=\"true\">&times;</span><span class=\"sr-only\">Close</span></button>
                                            <h4 class=\"modal-title\">QNA $NumQna $FecLim</h4>
                                            <small class=\"font-bold\">Resumen de Productos de Nómina.</small>
                                        </div>
                                        <div class=\"modal-body\">



<!-- inicio de cuerpo -->


                            <div class=\"forum-title\">
                                <div class=\"pull-right forum-desc\">
                                    <samll>Total Global: $TotalQuincenaFmto</samll>
                                </div>
                                <h3>Total por  Unidades Responsables </h3>
                            </div>


                            $BodyModal
<!-- fin de cuerpo -->

                                        </div>
                                        <div class=\"modal-footer\">
                                            <button type=\"button\" class=\"btn btn-white\" data-dismiss=\"modal\">Cerrar</button>
                                            <button type=\"button\" class=\"btn btn-primary\">Imprimir</button>
                                        </div>
                                    </div>
                                </div>
                     </div>


<!-- fin del modal -->

                    </div>
                </div>
                            ";
            //Seccion donde se extraen datos cargados
        }// fin de while
}
return $HeaderRow . $Body . $TailRow;

} // fin de obtenerHistoricoQnas($QnaUrl, $AnioUrl)

?>