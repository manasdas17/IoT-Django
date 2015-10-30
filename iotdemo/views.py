import json

from django.views import generic 
from django.core.urlresolvers import reverse 
from django.template import RequestContext, loader 
from django.shortcuts import render, get_object_or_404 
from django.http import HttpResponse, HttpResponseRedirect, JsonResponse  

from .models import Customer, Cake, Order 


class IndexView(generic.ListView):
	template_name = 'iotdemo/index.html'
	context_object_name = 'our_cakes'
	
	def get_queryset(self):
		return Cake.objects.all()


class CartView(generic.ListView):	
	template_name = 'iotdemo/cart.html'
	context_object_name = 'our_cakes'
	
	def get_queryset(self):
		latest = [] 
		cart = json.loads(self.request.session["cart"]) 
		count = self.request.session["count"] 
		cakes = Cake.objects.all() 
		
		# Probably not the best method if the # of items is large...
		for item in cart['items']:
			for cake in cakes:
				cakeid = str(cake.id)
				cakeitem = item.get(cakeid)
				if cakeitem:
					temp = {} 
					temp['id'] = cakeid 
					temp['label'] = cake.label 
					temp['price'] = str(cake.price) 
					temp['number'] = str(cakeitem) 
					temp['income'] = str(int(cakeitem)*int(cake.price))
					latest.append(temp) 
		return latest


def login(request): 
	username = email = ''
	request.session["success"] = ''
	request.session["customer"] = ''
	request.session["count"] = '0'
	request.session["cart"] = '{ "items": [] }'
	
	if request.POST:
		username = request.POST['username']
		email = request.POST['email']
		if email:
			# If user doesn't exist yet, just create the user. 
			try:
				customer = Customer.objects.get(email = email)
				request.session["customer"] = customer.id
			except Customer.DoesNotExist:
				customer = Customer(username = username, email = email)
				customer.save()
				request.session["customer"] = customer.id
	return HttpResponseRedirect(reverse('index'))


def addtocart(request):
	request.session["success"] = ''
	if request.GET and request.session["customer"] != '':
		request.session["cart"] = request.GET['cart']
		request.session["count"] = request.GET['count']
		return HttpResponse("OK") 
	else:
		return HttpResponse("-1") 


def checkout(request):
	if request.POST and request.session["customer"] != '':
		custid = str(request.session["customer"]) 
		customer = Customer.objects.get(id=custid)
		for key in request.POST:
			value = request.POST[key]
		# Won't need the value now, just in case of future use. 
		for key, value in request.POST.iteritems():
			if key.startswith('qty'):
				cid = key.split('_')[1]
				qty = request.POST['qty_'+cid]
				income = request.POST['income_'+cid]
				cake = Cake.objects.get(id=cid)
				if int(qty) > cake.quantity:
					qty = str(cake.quantity)
				# This means we sell all remaining cakes to the customer. 
				order = Order(customer=customer, cake=cake, number=qty, earnings=income)
				order.save()
				cake.quantity -= int(qty)
				cake.save()
		request.session["success"] = 'OK'
	else:
		request.session["success"] = ''
	request.session["count"] = '0'
	request.session["cart"] = '{ "items": [] }'
	return HttpResponseRedirect(reverse('index')) 


# Cake quantities are only verified to be > 0 upon final checkout. 
# Signup/login form doesn't actually perform strict checking for duplicate usernames, only emails. 
# In production code, it's probably better to use Django Forms for form validation, cleaning, etc. 


def price(request, device_id):
	cake = get_object_or_404(Cake, deviceid=device_id)
	price = "$" + str(cake.price)
	return HttpResponse("{" + price + "}")
	
	
def update(request, add_sub, device_id): 
	cake = get_object_or_404(Cake, deviceid=device_id)
	
	if add_sub == "add":
		cake.quantity += 1
		cake.save()
		return HttpResponse("{OK}")
		
	if add_sub == "sub":
		cake.quantity -= 1
		cake.save()
		return HttpResponse("{OK}")
		
	return HttpResponse("{Update failed.}")
	
