
<?php
/*
 * 
 */
echo  " 

<!DOCTYPE html>
<html>

<head>

    <meta charset=\"utf-8\">
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">

    <title>Olvido Password </title>

    <link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">
    <link href=\"font-awesome/css/font-awesome.css\" rel=\"stylesheet\">
<link href=\"css/animate.css\" rel=\"stylesheet\">
    <link href=\"css/style.css\" rel=\"stylesheet\">
    
    <script src=\"js/jquery.js\"></script>
    <script>
    $(function(){
        //alert(\"hola\");
      $(\"#correo\").keyup(function(){
        
        var param = $(\"#correo\").val();
        //alert(param);

         $(\"#resultado\").load('ptfma_busqueda.php',{parametro:param});
      });
    });
    </script>

</head>
<body class=\"gray-bg\">
                <table align=\"center\" height=\"60\">
  <tr>
     <td width=\"420\" align=\"left\"><img src=\"images/logoSALUD_hoz.png\" width=\"289\" height=\"95\" /></td>
     <!--<td width=\"420\" align=\"left\">
     <img src=\"images/70Salud.jpg\" width=\"375\" height=\"91\" /></td>-->
     <!--<td width=\"683\" align=\"right\">
     <div id=\"dominio\">Recepción Art. 74</div>
     </td>  -->  
     <td width=\"683\" align=\"right\">
             <div class=\"col-lg-10\">
                    <h2>Sistema de Recepción de Productos de Nómina</h2>
        </div>
     </td>    
  </tr>
</table> 
    <div class=\"passwordBox animated fadeInDown\">
        <div class=\"row\">
            <div class=\"col-md-12\">
              <div class=\"ibox-content\">
                    <h2 class=\"font-bold\">Recuperación de Credenciales</h2>
                    <p>Ingrese su email para reenviar sus credenciales de acceso.</p>
                <div class=\"row\">
                        <div class=\"col-lg-12\">
                            <form class=\"m-t\" role=\"form\" action=\"ptfma_recupera_email.php\" method=\"post\">
                                <div class=\"form-group\">
                                  <input type=\"email\" class=\"form-control\" id=\"correo\" placeholder=\"Email\" name=\"correo\" required=\"\" >
                                    </div>
                  <p>Responda la pregunta de seguridad</p>
                  <div class=\"form-group\">
                  <div id=\"resultado\"  name=\"respuestaa\" ></div>
                  </div>
                  <div class=\"form-group\">
                  <input type=\"text\" class=\"form-control\" id=\"parametro\" placeholder=\"Respuesta\" name=\"respuesta\" required=\"\" >
                  </div>
                  <button type=\"submit\" class=\"btn btn-primary block full-width m-b\">Comprobar Correo</button>
              </form>
                        </div>
                </div>";

/*
 * APARTADO DE LOS MENSAJES DE ERROR POR SI CORREO O RESPUESTA ESTAN MAL 
 */
                if (isset($_GET['msg'])){
                $Mensaje=" <span class=\"label label-primary\" 
                style=\"background-color: #F00404;\">" . $_GET['msg'] . "</span>";
                echo $Mensaje;
/*
 * TERMINACION DE ESTE APARTADO
 */
         }
               echo"
              </div>
            </div>
        </div>
        <hr/>
        <div class=\"row\">
            <div class=\"col-md-6\">
                &nbsp;
            </div>
            <div class=\"col-md-6 text-right\">
               <small>&nbsp;</small>
            </div>
        </div>
    </div>



      <div id=\"footerEPN\" style=\"clear:both; margin-top: 12px;\">
            <div style=\"clear: both; width: 100%; border-top: 1px solid #dedede; margin-bottom: 1px;\"></div>
            <div style=\"border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; font-family: 'Times New Roman', serif; font-size: 14px; color: #666666; text-align: center; padding: 14px 0px;\">SECRETAR&Iacute;A DE SALUD - ALGUNOS DERECHOS RESERVADOS &copy; 2012 - <a href=\"http://portal.salud.gob.mx/contenidos/inicio/politicas.html\" style=\"text-decoration: none; color: #808080;\">POL&Iacute;TICAS DE PRIVACIDAD</a></div>
            <div style=\"clear: both; width: 100%; border-top: 1px solid #dedede; margin-top: 1px;\"></div>
            
            <div style=\"clear:both; width: 100%;\">
                
              <div style=\"float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;\"></div>
                <div align=\"right\"><img src=\"images/logoSALUD_hoz.png\" width=\"220\" height=\"72\" style=\"float:left; margin: 0px 24px;\" align=\"middle\" />
                </div>
                <div style=\"float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;\"></div>
                <div style=\"clear: both; width: 100%;\"></div>
            </div>
            
            <div style=\"margin: 32px auto 42px auto; text-align: center; font-family: 'Times New Roman', serif; font-weight: lighter; font-size: 13px;\">
                <p style=\"color: #808080; line-height: 5px;\">Lieja No. 7, Col. Ju&aacuterez, Deleg. Cuauht&eacutemoc</p> 
                <p style=\"color: #808080; line-height: 5px;\">Distrito Federal CP. 06600 </p>
            </div>
            <div style=\"clear: both; width: 100%;\"></div>
        </div>
</div>

";//Ventana Modal: quiere decir que el correo se envio con exito
$var=utf8_encode('Reforma No. 156, 7 ° Piso');
if(isset($_GET['msgventana'])){
  echo "
<!DOCTYPE html>
<html lang='en'>
<head>
  <meta charset='UTF-8'>
  <title>Document</title>
  <meta name='viewport' content='width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0'>
  <script src='js/jquery.js'></script>
  <script src='js/bootstrap.min.js'></script>
  <script>
  $(function(){
    $('#mostrar').modal('show');
    $('#redireccionar').click(function(){
      window.location.href='http://www.ran.salud.gob.mx';
    });
  });
  </script>
</head>
<body>
  
<div class='modal inmodal' id='mostrar' data-keyboard='false' data-backdrop='static'>
  <br><br><br><br><br><br>
      <div class='modal-dialog'>
        <div class='modal-content animated flipInY\'>

          <!--Encabezado!-->
          <div class='modal-header'>
            
            <table class='col-xs-offset-1 col-sm-offset-1 col-md-offset-1 col-lg-offset-1'>
                <tr>
                  <td>
                    <img src='images/logoSALUD_hoz.png' width='170' height='80'>
                  </td>
                  <td>
                  &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
                  &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
                  &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
                  </td>
                  <td>
                    <h4>Sistema de Recepción de <br>Productos de Nómina</h4>
                  </td>
                 </tr>
            </table>
            
          </div>
          <!--Contenido!-->
          <div class='modal-body ' >
            <h4> <p align=''> &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspSolicitud Realizada:</p></h4>
            <p> &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspRevise su correo de entrada</p>
          </div>
          <!--Final, Pie de pagina!-->
          <div class='modal-footer'>
          <p align='center'>
          </p>
          <table>
            <tr>
            <td width='10'>

            </td>
              <td width='400'>
                <div text-align: center; font-family: 'Times New Roman', serif; font-weight: lighter; font-size:'5px;'>
                          <p align='center' style='color: #808080; line-height: 5px;'>Reforma No. 156, 7 Piso</p> 
                         <p align='center' style='color: #808080; line-height: 1px'>Col. Juárez, Del. Cuauhtémoc, C.P. 06600 México D.F.</p>
                         <p align='center' style='color: #808080; line-height: 5px'>Tel. (55) 50-62-16-00 Y (55) 50-62-17-00</p>
                         
                      </div>
              </td>
              
              <td>
                <button type='button' class='btn btn-primary' id='redireccionar'>&nbsp&nbsp&nbspSalir&nbsp&nbsp&nbsp</button>
              </td>
            </tr>
          </table>
            
            
          </div>
        </div>
      </div>
    </div><!--Pone la pantalla negra!-->
</body>
</html>
";
}

echo"

</body>

</html>
";

?>
