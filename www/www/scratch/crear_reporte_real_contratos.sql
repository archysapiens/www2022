create table RFC_ART_74 AS select distinct rfc
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur = 'CON';


create table RFC_ART_74_CMPLTO AS select  rfc, UR
from BDART742013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 and ur != 'CON'
GROUP BY rfc, UR;

create table RFC_ART_74_416 AS select  rfc, UR
from BD4162013
where qnaproc >= '16' and 
tipnom='11' and 
financiamiento not in (5,6,7,11,13) and
funcion !=10 
GROUP BY rfc, UR;


drop   table reporte_contratos;
create table reporte_contratos as select rfc,ur,curp,estado, qnaproc,anioproc from bdart742013 where rownum=1;
truncate table reporte_contratos;
select * from reporte_contratos;

insert into  reporte_contratos(rfc,ur) 
SELECT RA74.RFC, RA74C.UR 
FROM RFC_ART_74 RA74 inner  JOIN  RFC_ART_74_CMPLTO RA74C
ON  RA74.RFC=RA74C.RFC
union
SELECT RA74.RFC, RA74416.UR
FROM RFC_ART_74 RA74 inner  JOIN  RFC_ART_74_416 RA74416
ON  RA74.RFC=RA74416.RFC;


update reporte_contratos rc
set (curp,estado,qnaproc,anioproc) = ( select curp,estado,qnaproc,anioproc from BDART742013 bd
                        where  rc.rfc=bd.rfc and rc.ur=bd.ur and  
                         rownum=1 and  
                        qnaproc >= '16' and 
                        tipnom='11' and 
                        financiamiento not in (5,6,7,11,13) and
                        funcion !=10 )
                      

update reporte_contratos rc
set (curp,estado,qnaproc,anioproc) = ( select curp,estado,qnaproc,anioproc from BD4162013 bd
                        where  rc.rfc=bd.rfc and rc.ur=bd.ur and  
                         rownum=1 and  
                        qnaproc >= '16' and 
                        tipnom='11' and 
                        financiamiento not in (5,6,7,11,13) and
                        funcion !=10 )
where qnaproc is null  
