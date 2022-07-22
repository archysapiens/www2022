set @idremesa=10021;
set @etiqueta='01-2016-22-20161025122937-5';
set @archivo_err='prde040.dat';
set @fecha=now();
load data local infile '../staging/prde040.dat.err'
INTO TABLE errores
FIELDS TERMINATED BY '|' ENCLOSED BY '"'
LINES TERMINATED BY '\n'
(numero_registro,  campo, evidencia, descripcion)
set id_remesas=@idremesa, etiqueta_envio=@etiqueta,
archivo_error=@archivo_err,fecha_registro=@fecha;
