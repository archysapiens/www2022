set @idremesa=10018;
set @etiqueta='01-2016-19-20160906172228-5';
set @archivo_err='prde01r.tra';
set @fecha=now();
load data local infile '../staging/prde01r.tra.err'
INTO TABLE errores
FIELDS TERMINATED BY '|' ENCLOSED BY '"'
LINES TERMINATED BY '\n'
(numero_registro,  campo, evidencia, descripcion)
set id_remesas=@idremesa, etiqueta_envio=@etiqueta,
archivo_error=@archivo_err,fecha_registro=@fecha;
