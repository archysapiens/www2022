select rfc, 
(SELECT  LISTAGG(rd2.ur, '-') WITHIN GROUP (ORDER BY rd2.rfc,rd2.estado) 
              FROM   reporte_contrato_debug  rd2
              where rd.rfc=rd2.rfc and rd.estado=rd2.estado and rd2.anioenv='2016' and rd2.qnaenvio='17'
              GROUP BY rfc,estado,rd2.rfc) as a16,
(SELECT  LISTAGG(rd2.ur, '-') WITHIN GROUP (ORDER BY rd2.rfc,rd2.estado) 
              FROM   reporte_contrato_debug  rd2
              where rd.rfc=rd2.rfc and rd.estado=rd2.estado and rd2.anioenv='2016' and rd2.qnaenvio='17'
              GROUP BY rfc,estado,rd2.rfc) as a17,
              (SELECT  LISTAGG(rd2.ur, '-') WITHIN GROUP (ORDER BY rd2.rfc,rd2.estado) 
              FROM   reporte_contrato_debug  rd2
              where rd.rfc=rd2.rfc and rd.estado=rd2.estado and rd2.anioenv='2016' and rd2.qnaenvio='18'
              GROUP BY rfc,estado,rd2.rfc) as a18
from reporte_contrato_debug rd;