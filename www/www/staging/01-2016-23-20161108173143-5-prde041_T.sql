set @idremesa=10022;
set @etiqueta='01-2016-23-20161108173143-5';
set @archivo_err='prde041.tra';
set @fecha=now();
load data local infile '../staging/prde041.tra.err'
INTO TABLE errores
FIELDS TERMINATED BY '|' ENCLOSED BY '"'
LINES TERMINATED BY '\n'
(numero_registro,  campo, evidencia, descripcion)
set id_remesas=@idremesa, etiqueta_envio=@etiqueta,
archivo_error=@archivo_err,fecha_registro=@fecha;
