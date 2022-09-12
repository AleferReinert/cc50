-- Keep a log of any SQL queries you execute as you solve the mystery.

--Carros que sairam do tribunal após o roubo:
SELECT * FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit";

--Pesoas que sairam do tribunal após o roubo:
SELECT * FROM people WHERE license_plate in (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit");

-- Aeroporto de Fiftyville
SELECT * FROM airports WHERE city = "Fiftyville";

-- Voo do ladrão
SELECT * FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;

-- Cidade para qual o ladrão fugiu:
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

-- Lista de passageiros
SELECT * FROM passengers WHERE flight_id = 36;

-- Lista de passageiros que sairam do tribunal após o roubo:
SELECT * FROM people WHERE passport_number in (SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate in (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit")));

-- Ligações feitas pelos 3 principais suspeitos, que dispensa Danielle e sobra Madison e Ernest:
SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller in (SELECT phone_number FROM people WHERE passport_number in (SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate in (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit"))) AND id IN (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ORDER BY amount))));

-- Retiradas de dinheiro feitas pelo ladrão:
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ORDER BY amount;

-- Pessoas que fizeram saque:
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ORDER BY amount));

-- Pessoas que fizeram saque, sairam do tribunal e estão na lista de passageiros:
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit"))) AND id IN (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ORDER BY amount)));

-- Pessoas que fizeram saque, sairam do tribunal, estão na lista de passageiros e fizeram ligações:
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit"))) AND id IN (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ORDER BY amount)))));

-- Depósitos para compra da passagem:
SELECT * FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "deposit";

-- RESULTADOS:
-- CIDADE PARA QUAL O LADRÃO FUGIU:
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

-- CUMPLICE:
SELECT name FROM people WHERE id = (SELECT person_id FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = "exit"))) AND id IN (SELECT id FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street" ORDER BY amount)))))))));

-- LADRÃO:
SELECT name FROM people WHERE phone_number = (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND receiver in (SELECT phone_number FROM people WHERE id = 864400));