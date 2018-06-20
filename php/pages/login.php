<?php 
if (!defined("IN_LOGGER")) die("Access denied!");
include 'header.php' ?>

    <div class="container">
      <div class="row">
        <div class="col-lg-12"><br />
	 <form action="/?page=login" method="post">
	    <div class="form-group">
	      <label for="pwd">Password:</label>
	      <input type="password" class="form-control" id="pwd" name="pwd" placeholder="Enter password" name="pswd">
	    </div>
	    <button type="submit" class="btn btn-primary">Connexion</button>
	  </form>
        </div>
      </div>
    </div>
<?php

if (isset($_POST['pwd'])) {
	if (password_verify($_POST['pwd'], $pass)) {
	    $token = md5(microtime().rand());
	    $_SESSION['login'] = true;
	    $_SESSION['token'] = $token;
	    header("location:".$domaine."?token=".$token);
	}
        
}

include 'footers.php';

