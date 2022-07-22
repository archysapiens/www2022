<?php ob_start();
include "../general/DBC.php";
include "../general/DBCORA.php";
include "../general/generales.inc";
include "ptfma_registro.inc";
$db = new DbCnnx(); 
$dbOracle = new DbOraCnnx(); 

$sqlEstados="SELECT * FROM CAT_ESTADOS ORDER BY ID_ESTADO ASC "; $cat_estados=$dbOracle->combo($sqlEstados);

$sqlUnid="SELECT DISTINCT UR,DESCRIPCION FROM CAT_UR ORDER BY UR"; $cat_ur=$dbOracle->combo($sqlUnid);

$sqlPregunta="SELECT * FROM pregunta"; $pregunta=$db->combo($sqlPregunta);

echo fncBuildHead();
echo fncBuildBody($cat_estados,$cat_ur,$pregunta);
echo fncBuildJS();

if (isset($_POST['submitConfirmarAlta'])) {
	switch($_POST['submitConfirmarAlta']) {
		case "confirmar":
		
		@$id= $_POST['txt_email'];
		$Query="Select * from usuarios where id='$id';";
			$result = $db->select($Query);
			if($result){
				echo "<script>msgUser();</script>";
				unset($_POST);
			}else{
		
				$target_path = "../images/FileUpload/";
				$target_path = $target_path . basename( $_FILES['txt_foto']['name']);
				move_uploaded_file($_FILES['txt_foto']['tmp_name'], $target_path);
			
				@$count = count(@$_POST['txt_creden']);$array=@$_POST['txt_creden'];
				if($count==1){$credenciales = $array[0];} 
				elseif($count==2){$credenciales = $array[0].",".$array[1];}
				elseif($count==3){$credenciales = $array[0].",".$array[1].",".$array[2];} 
				elseif($count==4){$credenciales = $array[0].",".$array[1].",".$array[2].",".$array[3];}

				@$nombre = $_POST['txt_nombre'];
				@$app_paterno = $_POST['txt_app_p'];
				@$app_materno = $_POST['txt_app_m'];
				@$sexo= $_POST['sexo'];
				@$edad=$_POST['txt_edad'];
				@$fecha_nac= $_POST['txt_fech_nac'];
				@$tel_oficina = $_POST['txt_tel_ofi'];
				@$extension = $_POST['txt_ext'];
				@$tel_mobil = $_POST['txt_tel_per'];
				@$organismos = $_POST['txt_organismos'];
				@$unid_respon = $_POST['txt_uni_respon'];
				@$pregunta=$_POST['txt_pregunta_seguridad'];
				@$respuesta=$_POST['txt_respuesta'];
				@$password = $_POST['txt_psw'];
				
				$SQL = "INSERT INTO usuarios VALUES ('$id','$nombre','$app_paterno','$app_materno','$sexo','$edad','$fecha_nac','$target_path','$tel_oficina','$extension','$tel_mobil','$organismos','$unid_respon','(NULL)','$pregunta','$respuesta','$password')";
				$row = $db->query($SQL);
				foreach($array as $rows){
					$SQL2 = "INSERT INTO privilegios VALUES (NOW(),'$organismos','$id','I',NOW(),$rows);";
					$row = $db->query($SQL2);
				}
				include("ptfma_AltaUsuario.php");
								
			}
				unset($_POST);
		BREAK;
	}
}					
ob_end_flush() ?>