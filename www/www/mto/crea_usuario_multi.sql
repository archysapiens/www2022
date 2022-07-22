//// script para un usuario Multiperfil


INSERT INTO usuarios
            (id,
             nombre,
             app_paterno,
             app_materno,
             sexo,
             edad,
             fecha_nacimiento,
             foto,
             tel_oficina,
             extension,
             tel_mobil,
             organismos,
             unidad_responsable,
             credenciales,
             pregunta,
             respuesta,
             password)
VALUES ('multi@salud.gob.mx',
        'Multiperfil',
        'Multiperfil',
        'Multiperfil',
        'M',
        45,
        STR_TO_DATE('01-01-1970', '%m-%d-%Y'),
        null,
        '7282822744',
        null,
        null,
        null,
        null,
        null,
        null,
        null,
        '123');


INSERT INTO privilegios
    (fecha,
     id_organismos,
     id_usuarios,
     estatus,
     fecha_actualizacion,
     id_roles)
VALUES (curdate(),
        '20',
        'multi@salud.gob.mx',
        'A',
        curdate(),
        '10');


INSERT INTO privilegios
    (fecha,
     id_organismos,
     id_usuarios,
     estatus,
     fecha_actualizacion,
     id_roles)
VALUES (CURDATE(),
        '20',
        'multi@salud.gob.mx',
        'A',
        CURDATE(),
        '20');

INSERT INTO privilegios
    (fecha,
     id_organismos,
     id_usuarios,
     estatus,
     fecha_actualizacion,
     id_roles)
VALUES (CURDATE(),
        '20',
        'multi@salud.gob.mx',
        'A',
        CURDATE(),
        '30');                

INSERT INTO privilegios
    (fecha,
     id_organismos,
     id_usuarios,
     estatus,
     fecha_actualizacion,
     id_roles)
VALUES (CURDATE(),
        '20',
        'multi@salud.gob.mx',
        'A',
        CURDATE(),
        '40');                        