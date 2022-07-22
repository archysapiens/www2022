set @idremesa=10014;
set @etiqueta='01-2016-15-20160721173852-5';
set @archivo_err='chcn01p';
set @fecha=now();
load data local infile '../staging/chcn01p.dat.err'
INTO TABLE errores
FIELDS TERMINATED BY '|' ENCLOSED BY '"'
LINES TERMINATED BY '\n'
(numero_registro,  campo, evidencia, descripcion)
set id_remesas=@idremesa, etiqueta_envio=@etiqueta,
archivo_error=@archivo_err,fecha_registro=@fecha;