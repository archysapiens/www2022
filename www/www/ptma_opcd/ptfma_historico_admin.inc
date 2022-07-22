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
$HeaderRow = "  <!-- Inicio de row -->
                <div class=\"row animated fadeIn\">";
$script = " 
<script>
$(function(){
    $('a').click(function(){
        var idQna=event.target.id;
        
        var anio='&&anio='+idQna.substring(0,4);
        var Qna='?Qna='+idQna.substring(4,idQna.lenght)+anio;
        
        var numero=idQna.substring(0,4);
        
        if($.isNumeric(numero)){
            window.location.href='ptfma_admin.php'+Qna;
        }else{
             window.location.href='ptfma_admin.php';
        }
        
    });
});
</script>
";
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
            //muestra las Sumas de Percepciones y deducciones por quincena

           $SQL_Percep_Deduc="SELECT SUM(percepciones) as Percepciones, SUM(deducciones) as Deducciones,(SUM(deducciones)+SUM(percepciones))as total, numero_periodos as Quincena
           FROM remesas inner join log_carga on id=id_remesas 
           WHERE numero_periodos=$NumQna AND numero_periodos<=$QnaUrl;";

            $rows2=$db->select($SQL_Percep_Deduc);
            
            $Percepciones=$rows2[0]['Percepciones'];
            $Deducciones =$rows2[0]['Deducciones'];
            $Total       =$rows2[0]['total'];
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
                    $TipoCarga=str_replace($TipoCarga, '@', " ");
                    $DescCarga=str_replace($DescCarga, '@', " ");
                    $EstatusCarga=str_replace($EstatusCarga, '@', " ");
                    $FechaCarga==str_replace($FechaCarga, '@', " ");
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
            

            $Body .= "<div class=\"col-md-4\">
                    <div class=\"panel $PanelColor\">
                        <div class=\"panel-heading\">
                            <div class=\"row\">
                                <div class=\"col-xs-3\">
                                    <i class=\"$Icono\"></i>
                                </div>
                                <div class=\"col-xs-9 text-right\">
                                    <div class=\"huge\">QUINCENA $NumQna </div>
                                    <div>T.P. $ $Percepciones</div>
                                    <div>T.D. $ $Deducciones</div>
                                    <div>Total: $ $Total</div>
                                    <!--<div> $Configuracion </div>!-->

                                </div>
                            </div>
                        </div>
                        <a href=\"#\" id=\"$Anio$NumQna\" data-toggle=\"modal\" data-target=\"#\">
                            <div class=\"panel-footer\" id=\"$Anio$NumQna\">
                                <span class=\"pull-left\" id=\"$Anio$NumQna\">Ver Detalles</span>
                                <span class=\"pull-right\"id=\"$Anio$NumQna\">
                                <i class=\"fa fa-arrow-circle-right\" id=\"$Anio$NumQna\"></i></span>
                                <div class=\"clearfix\" id=\"$Anio$NumQna\"></div>
                            </div>
                        </a>



                    </div>
                </div>
                            ";
            //Seccion donde se extraen datos cargados
        }// fin de while
}

return $HeaderRow . $Body .$TailRow .$script;

} // fin de obtenerHistoricoQnas($QnaUrl, $AnioUrl)

?>