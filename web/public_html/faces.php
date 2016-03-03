<?php
// TODO: Melhorar tratamento de erros
$file_path = '../faces.xml';
if (file_exists($file_path)) {
    $img = file_get_contents($file_path);
    if ($img) {
        header("Content-type:text/xml");
        echo $img;
    } else {
        http_response_code(503);
    }
} else {
    http_response_code(503); // Serviço indisponível
}
