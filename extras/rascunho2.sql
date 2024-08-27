SELECT d.cid, d.nome_tecnico, np.nome AS "nome popular", p.nome_cientifico, p.tipo, GROUP_CONCAT(s.nome SEPARATOR ', ') AS "sintomas"
FROM doencas AS d
LEFT JOIN doenca_sintoma as ds ON d.cid = ds.id_doenca
LEFT JOIN sintomas AS s ON ds.id_sintoma = s.id
LEFT JOIN nome_popular AS np ON np.id_doenca = d.cid
LEFT JOIN patogenos AS p ON p.id = d.id_patogeno

WHERE d.nome_tecnico = "Raiva";

GROUP BY d.cid, d.nome_tecnico, np.nome, p.nome_cientifico, p.tipo;

# SELECT d.cid, d.nome_tecnico, np.nome AS nome_popular, p.nome_cientifico, p.tipo, GROUP_CONCAT(s.nome SEPARATOR ', ') AS sintomas FROM doencas AS d LEFT JOIN doenca_sintoma as ds ON d.cid = ds.id_doenca LEFT JOIN sintomas AS s ON ds.id_sintoma = s.id LEFT JOIN nome_popular AS np ON np.id_doenca = d.cid LEFT JOIN patogenos AS p ON p.id = d.id_patogeno WHERE d.nome_tecnico = 'Raiva'; GROUP BY d.cid, d.nome_tecnico, np.nome, p.nome_cientifico, p.tipo;