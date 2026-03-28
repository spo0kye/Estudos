package controllers

import (
	"go-htmx/internal/services"
	"html/template"
	"net/http"
	"strconv"
)

var Templates *template.Template

func PizzasPage(w http.ResponseWriter, r *http.Request) {
	pizzas, _ := services.ListPizzas()
	Templates.ExecuteTemplate(w, "layout", pizzas)
}

func AddPizza(w http.ResponseWriter, r *http.Request) {
	name := r.FormValue("name")
	price := r.FormValue("price")

	if len(price) < 1 || len(name) < 1 {
		panic("Invalid input: name or price")
	}

	fprice, err := strconv.ParseFloat(price, 64)
	if err != nil {
		panic("Invalid price")
	}

	services.AddPizza(name, fprice)

	pizza := services.FindPizza(name)

	Templates.ExecuteTemplate(w, "pizza", pizza)
}
