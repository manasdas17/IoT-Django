
How to install this app into a new or existing Django project... 


0. Create a new Django project if necessary: <br/>
<br/>
$ django-admin startproject nameofprojectwebsite <br/>
$ cd nameofprojectwebsite <br/>
$ python manage.py migrate <br/>
$ python manage.py createsuperuser <br/>

<br/>
1. Edit the project's "settings.py" and add: <br/>
<br/>
INSTALLED_APPS = (<br/>
	''' Stuff that was already there... ''' <br/> 
	'iotdemo',<br/>
)<br/>
TEMPLATE_CONTEXT_PROCESSORS = (<br/>
	"django.core.context_processors.auth", <br/>
	"django.core.context_processors.debug", <br/>
	"django.core.context_processors.i18n", <br/>
	"django.core.context_processors.media", <br/>
	"django.core.context_processors.request", <br/>
)<br/>
*For Django v1.7 only! Use something else for v1.8. <br/>

<br/>
2. Edit the project's "urls.py" and change: <br/>
<br/>
urlpatterns = patterns('',<br/>
	''' Stuff that was already here... '''<br/>
	url(r'^iotdemo/', include('iotdemo.urls', namespace="iotdemo")), <br/>
	url(r'^admin/', include(admin.site.urls)), <br/>
) <br/>

<br/>
3. Update the database with models: <br/>
<br/>
$ python manage.py makemigrations iotdemo <br/>

---

To start the server in background with public-facing website: <br/>
<br/>
$ sudo nohup  python manage.py runserver 0.0.0.0:80 & <br/>

