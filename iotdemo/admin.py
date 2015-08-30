import datetime

from django.utils import timezone
from django.contrib import admin

from .models import Cake, Customer, Order


class CakeAdmin(admin.ModelAdmin):
  fieldsets = [
    (None, {'fields': ['label']}),
    (None, {'fields': ['price']}),
    (None, {'fields': ['quantity']}),
  ]
  
  search_fields = ['label']
  list_display = ('label', 'price', 'quantity')


class CustomerAdmin(admin.ModelAdmin):
  fieldsets = [
    (None, {'fields': ['username']}),
    (None, {'fields': ['email']}),
  ]
  
  search_fields = ['username']
  list_display = ('username', 'email')
  

class OrderAdmin(admin.ModelAdmin):
  fieldsets = [
    (None, {'fields': ['customer']}),
    (None, {'fields': ['cake']}),
    (None, {'fields': ['number']}),
    (None, {'fields': ['earnings']}),
  ]
  
  list_filter = ['date']
  list_display = ('customer', 'cake', 'date', 'number', 'earnings')


admin.site.register(Cake, CakeAdmin)
admin.site.register(Customer, CustomerAdmin)
admin.site.register(Order, OrderAdmin)



