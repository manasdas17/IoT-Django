
How to install this app into a new or existing Django project... 


(0) Create a new Django project if necessary: <br/>
<br/><pre lang="bash"><code>
$ django-admin startproject nameofprojectwebsite 
$ cd nameofprojectwebsite 
$ python manage.py migrate 
$ python manage.py createsuperuser 
</pre></code>
<br/>
(1) Edit the project's "settings.py" and add: <br/>
<br/><pre lang="python"><code>
INSTALLED_APPS = (
	''' Stuff that was already there... '''  
	'iotdemo',
)
TEMPLATE_CONTEXT_PROCESSORS = (
	"django.core.context_processors.auth", 
	"django.core.context_processors.debug", 
	"django.core.context_processors.i18n", 
	"django.core.context_processors.media", 
	"django.core.context_processors.request", 
)
#For Django v1.7 only! Use something else for v1.8. 
</pre></code><br/>
<br/>
(2) Edit the project's "urls.py" and change: <br/>
<br/><pre lang="python"><code>
urlpatterns = patterns('', 
	''' Stuff that was already here... ''' 
	url(r'^iotdemo/', include('iotdemo.urls', namespace="iotdemo")), 
	url(r'^admin/', include(admin.site.urls)), 
) 
</pre></code><br/>
<br/>
(3) Update the database with models: <br/>
<br/>
$ python manage.py makemigrations iotdemo <br/>
<br/>
---

To start the server in background with public-facing website: <br/>
<br/>
$ sudo nohup  python manage.py runserver 0.0.0.0:80 & <br/>

