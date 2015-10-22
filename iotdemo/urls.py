from django.contrib import admin
from django.conf.urls import include, url

from . import views


urlpatterns = [
	url(r'^$', views.IndexView.as_view(), name='index'),
	url(r'^login/', views.login, name='login'),
	url(r'^cart/', views.CartView.as_view(), name='cart'),
	url(r'^addtocart/', views.addtocart, name='addtocart'),
	url(r'^checkout/', views.checkout, name='checkout'),
	url(r'^price/(?P<device_id>\w+)/$', views.price, name='price'),
	url(r'^update/(?P<add_sub>\w+)/(?P<device_id>\w+)/$', views.update, name='update'),
] 


