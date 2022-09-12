SELECT TITLE FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE id in (SELECT movie_id FROM stars WHERE person_id in (SELECT id FROM people WHERE name = "Chadwick Boseman")) ORDER BY ratings.rating DESC LIMIT 5;