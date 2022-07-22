<?php
include "./general/DBC.php";
include "./general/generales.inc";
require_once('class.phpmailer.php');
$db       =new DbCnnx();

/*
 * consulta de correo y respuesta de seguridad
 */
 $Correo   =$_POST['correo'];
 $respuesta =utf8_decode($_POST['respuesta']);
    
 	$Consulta_correo="SELECT nombre,password FROM usuarios WHERE respuesta='".$respuesta."' AND id='".$Correo."'";
	$Rows = $db->select($Consulta_correo);
	
	if(!$Rows){
		header("Location:ptfma_recuperar_pwd.php?msg=Correo o Respuesta incorrectas");

	}else{
		$Contador=CERO;
		if(is_array($Rows)){
			$Password  = $Rows[$Contador]['password'];
$mail = new PHPMailer(); 
$mail->IsSMTP(); 
$mail->SMTPAuth = true; 
$mail->SMTPSecure = "ssl"; 
$mail->Host = "smtp.gmail.com"; 
$mail->Port = 465; 
$mail->Username = "secretaria.salud.2017@gmail.com"; 
$mail->Password = "Gmaapache";
    
$mail->SetFrom('secretaria.salud.2017@gmail.com', utf8_decode('Sistema Secretaría de Salud'));
$mail->Subject = utf8_decode("Recuperacion de contraseña"); 
$mail->AltBody = ''; 
$mail->MsgHTML('<!DOCTYPE html>
              <html lang="en">
                <head>
                    <meta charset="utf-8">
              </head>
              <body>

                     <table align="center" height="60">
                    <tr>
                      <td width="420" align="left"><img src="http://www.oic.salud.gob.mx/images/logo_Footer.png" width="289" height="95" /></td>
     
                      <td width="683" align="right">
                            <div class="col-lg-10">
                                  <h2><p style="color: #808080; line-height: 5px;">Sistema de Recepci&oacute;n de Productos de N&oacute;mina</p></h2>
                          </div>
                      </td>    
                      </tr>
                 </table>

                             <p>Estimado usuario: <b>'.$Correo.'</b> </p> 
                             Recientemente usted solicit&oacute; recuperar su contrase&ntilde;a. Si solicit&oacute; usted su contrase&ntilde;a, por favor haga clic en el siguiente enlace para iniciar sesi&oacute;n:
                            <p style="color: #808080; line-height: 5px;">Tu contrase&ntilde;a es <b>'.$Password .'</b></p> 

              <p style="color: #808080; line-height: 5px;"><a href ="http://www.ran.salud.gob.mx">Iniciar Sesi&oacute;n</a></p> 
              
              <br>
              Si no ha realizado esta solicitud, p&oacute;ngase en contacto con su proveedor de servicios.
              <br>
              Atentamente, SECRETAR&Iacute;A DE SALUD.
              <br><br><br><br><br><br>
              <div id="footerEPN" style="clear:both; margin-top: 12px;">
              <div style="clear: both; width: 100%; border-top: 1px solid #dedede; margin-bottom: 1px;"></div>
              <div style="border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; font-family: "Times New Roman", serif; font-size: 14px; color: #666666; text-align: center; padding: 14px 0px;\">&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
              &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspSECRETAR&Iacute;A DE SALUD - ALGUNOS DERECHOS RESERVADOS &copy; 2012 - <a href="http://portal.salud.gob.mx/contenidos/inicio/politicas.html" style="text-decoration: none; color: #808080;">POL&Iacute;TICAS DE PRIVACIDAD</a></div>
              <div style="clear: both; width: 100%; border-top: 1px solid #dedede; margin-top: 1px;"></div>
                    <div style="clear:both; width: 100%;">
                               <div style="float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;"></div>
                         <div align="right"><img src="http://www.oic.salud.gob.mx/images/logo_Footer.png" width="220" height="72" style="float:left; margin: 0px 24px"; align="middle" /></div>
                         <div style="float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;"></div>
                         <div style="clear: both; width: 100%;"></div>
                    </div>
            
                     <div style="margin: 32px auto 42px auto; text-align: center; font-family: "Times New Roman", serif; font-weight: lighter; font-size: 13px;">
                         <p style="color: #808080; line-height: 5px;">Lieja No. 7, Col. Ju&aacuterez, Deleg. Cuauht&eacutemoc</p> 
                         <p style="color: #808080; line-height: 5px;">Distrito Federal CP. 06600 </p>
                     </div>
                     <div style="clear: both; width: 100%;"></div>
                  </div>
            </body>
          </html> ');  
$mail->AddAddress($Correo, "Destinatario");  
$mail->IsHTML(true); 

 if(!$mail->Send()) { 
// echo "Error: " . $mail->ErrorInfo; 
header("Location:ptfma_recuperar_pwd.php?msg=Lo sentimos tuvimos problemas al responder tu solicitud vuelve a intentarlo");
 } else { 
// echo "Mensaje enviado correctamente"; 
 header("Location:ptfma_recuperar_pwd.php?msgventana='Enviando_correo'");//DESTINO DE ENVIO DE CORREO EXITOSO
 }

			
}
    
			
         }

	

?>
