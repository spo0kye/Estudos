-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = "2020" AND street = "Chamberlin Street";


SELECT transcript FROM interviews WHERE day = "28" AND month = "7" AND year = "2020" AND transcript like "%courthouse%";

SELECT amount FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = "28" AND month = "7" AND year = "2020";

SELECT DISTINCT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit" AND name IN

(SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street") AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND hour = 8));


SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration < "60" AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));