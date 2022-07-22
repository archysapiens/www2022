<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptma_opcd.inc";
include "ptfma_admin.inc";
$db=new DbCnnx();

echo "<br>";
echo $archivo=$_FILES['archivo']["name"][0];
echo "<br>";
echo $comen=$_POST['comentario'];
echo "<br>";
echo $tagenvio1=$_POST['hidden1'];
echo "<br>";
echo $idreme=$_POST['hidden2'];
echo "<br>";


if	(isset($_FILES['archivo']) && isset($_POST['comentario']) && isset($_POST['hidden1']) && isset($_POST['hidden2']))
{
$tagenvio=$_POST['hidden1'];//////  TAGENVIO
$idremesa=$_POST['hidden2'];////////  ID_REMESAS



$observacion=$_POST['comentario'];//observaciones
date_default_timezone_set("America/Mexico_City");
$tiempo="20".date("y-m-d")." ".date("h:i:s");//fecha en tiempo real
$carpetaDestino="../staging/";//carpeta destino
 
    # si hay algun archivo que subir
    if($_FILES["archivo"]["name"][0])
    {
        # recorremos todos los arhivos que se han subido
        for($i=0;$i<count($_FILES["archivo"]["name"]);$i++)
        {
            # si es un formato de imagen
            if($_FILES["archivo"]["type"][$i]=="image/jpeg" || $_FILES["archivo"]["type"][$i]=="image/pjpeg" || $_FILES["archivo"]["type"][$i]=="image/gif" || $_FILES["archivo"]["type"][$i]=="image/png" ||$_FILES["archivo"]["type"][$i]=="application/pdf" || $_FILES["archivo"]["type"][$i]=="image/jpg")
            {
                # si exsite la carpeta o se ha creado
                if(file_exists($carpetaDestino) || @mkdir($carpetaDestino))
                {
                    $origen=$_FILES["archivo"]["tmp_name"][$i];//nombre del archivo original antes de renombrarlo

                    $destino=$carpetaDestino.$tagenvio."-".$_FILES["archivo"]["name"][$i];//nombre del archivo renombrado con ruta de carpeta STAGING
                    

//parte antes de mover el archivo donde se ara el update                    


$SQLinserlogger="
INSERT INTO `logger` (`id_remesas`, `fecha_registro`, `fecha_validacion`, `fecha_carga`, `tipo_archivo`, `archivo`, `registros`, `observaciones`, `etiqueta_envio`, `archivo_error`, `registros_error`, `estatus`, `id_tipo_nom`, `fecha_agregacion`) VALUES 
('".$idremesa."', '".$tiempo."', '".$tiempo."','".$tiempo."', 'A', '".$destino."', '0','".$observacion."' ,'".$tagenvio."', NULL, NULL, 'A', NULL, '".$tiempo."')
	";
	$Rows = $db->select($SQLinserlogger);

















//parte antes de mover el archivo donde se ara el update
                    # movemos el archivo
                    if(@move_uploaded_file($origen, $destino))
                    {
                        echo "<br>";
                        echo "<br>";
                        echo "<br>";
echo '<script language="javascript">alert("ARCHIVOS SUBIDOS");</script>';
//variables de saida para enviar a ptfma_producto.php
//en este archivo tambien deben entrar ocultas estas variables para redireccionar no para insertar sino para REDIRECCIONAR
//anioquincenaurl
//quincenaurl
                        //header("Location:ptfma_producto.php?quincenaurl=$Qna&anioquincenaurl=$Anio");//REDIRECCIONAMIENTO CON VARIEBLES AÑO Y QUINCENA
                        
                    }else{
                        //echo "<br>No se ha podido mover el archivo: ".$_FILES["archivo"]["name"][$i];
                        echo '<script language="javascript">alert("No se ha podido mover el archivo: ");</script>';
                    }
                }else{
                    //echo "<br>No se ha podido crear la carpeta: up/".$user;
                    echo '<script language="javascript">alert(" No se ha podido crear la carpeta:");</script>';
                }
            }else{
                //echo "<br>".$_FILES["archivo"]["name"][$i]." - NO es imagen jpg";
                echo '<script language="javascript">alert(" NO ES PERMITIDOS");</script>';

            }
        }
    }
    else{
        echo '<script language="javascript">alert("  No se ha subido ninguna imagen ");</script>';
        //echo "<br>No se ha subido ninguna imagen";
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}else{
    echo '<script language="javascript">alert("  ERROR");</script>';
	
}
?>
