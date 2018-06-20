<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
 
    <title>ULogger</title>

    <!-- Bootstrap core CSS -->
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.0/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.0/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.0/js/bootstrap.min.js"></script>
    <!-- Custom styles for this template -->
    <style>
      body {
        padding-top: 54px;
      }
      @media (min-width: 992px) {
        body {
          padding-top: 56px;
        }
      }

    </style>

  </head>

 
  <body>

    <!-- Navigation -->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top">
      <div class="container">
        <a class="navbar-brand" href="<?php echo $domaine ?>"> <img src="<?php echo $domaine ?>pages/logo-inverse.png" height="32" width="32"> ULogger</a>
        <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarResponsive">
          <ul class="navbar-nav ml-auto"> 
            <li class="nav-item">
              <a class="nav-link" data-toggle="modal" href="#keyloggerHelp">Help</a>
            </li> 
            <li class="nav-item">
              <a class="nav-link" href="<?php echo $domaine ?>?page=logout">Logout</a>
            </li>
          </ul>
        </div>
      </div>
    </nav>
	<!-- Modal -->
	<div class="modal fade" id="keyloggerHelp" tabindex="-1" role="dialog" aria-labelledby="exampleModalCenterTitle" aria-hidden="true">
	  <div class="modal-dialog modal-dialog-centered" role="document">
	    <div class="modal-content">
	      <div class="modal-header">
		<h5 class="modal-title" id="exampleModalLongTitle">Keylogger help</h5>
		<button type="button" class="close" data-dismiss="modal" aria-label="Close">
		  <span aria-hidden="true">&times;</span>
		</button>
	      </div>
	      <div class="modal-body">
 
		  <table class="table table-striped">
		    <thead>
		      <tr>
			<th>Key</th>
			<th>Value</th>
		      </tr>
		    </thead>
		    <tbody>
		      <tr>
			<td><span class="badge badge-secondary">[Return]</span></td>
			<td>"Return"</td>
		      </tr>
		      <tr>
			<td><span class="badge badge-secondary">[KP_Enter]</span> </td>
			<td>"Return"</td>
		      </tr>
		      <tr>
			<td><span class="badge badge-secondary">[Escape]</span></td>
			<td>"Esc"</td>
		      </tr>
		      <tr>
			<td><span class="badge badge-secondary">[BackSpace]</span></td>
			<td>"Bsp"</td>
		      </tr>
		    </tbody>
		  </table>
	      </div>
	      <div class="modal-footer">
		<button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
	      </div>
	    </div>
	  </div>
	</div> 
