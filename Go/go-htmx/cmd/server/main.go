package main

import (
	"go-htmx/internal/controllers"
	"go-htmx/internal/database"
	"html/template"
	"net/http"
)

var templates = template.Must(template.ParseGlob("templates/**/*.html"))

var counter = 0

func main() {
	database.Connect()

	controllers.Templates = templates

	http.HandleFunc("/", controllers.PizzasPage)
	http.HandleFunc("/pizzas/add", controllers.AddPizza)

	for _, t := range templates.Templates() {
		println(t.Name())
	}

	http.ListenAndServe("127.0.0.1:8080", nil)
}
