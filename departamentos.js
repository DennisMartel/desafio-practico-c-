$(document).ready(function() {
    /// AÑADE UN NUEVO REGISTRO
    $('#form-add').on('submit', function(e) {
        e.preventDefault();
        var form = this;
        $.ajax({
            url: $(form).attr('action'),
            method: $(form).attr('method'),
            data: new FormData(form),
            processData: false,
            dataType: 'json',
            contentType: false,
            beforeSend: function() {
                $(form).find('span.error-text').text('');
                $('#btn-save').text('Procesando datos por favor espere...')
            },
            success: function(data) {
                if (data.code == 0) {
                    $('#btn-save').text('Guardar')
                    $.each(data.error, function(prefix, val) {
                        $(form).find('span.' + prefix + '_error').text(val[0]);
                    });
                } else {
                    $(form)[0].reset();
                    $('#btn-save').text('Guardar')
                    $('.img-holder').empty();
                    $('.modal').modal('hide');
                    getDepartamentos();
                    toastr.success(data.msg);
                }
            }
        });
    });

    /// MUESTRA LA IMAGEN A SUBIR
    $('input[type="file"][name="imagen"]').val();
    $('input[type="file"][name="imagen"]').on('change', function() {
        var img_path = $(this)[0].value;
        var img_holder = $('.img-holder');
        var extension = img_path.substring(img_path.lastIndexOf('.') + 1).toLowerCase();

        if (extension == 'jpeg' || extension == 'jpg' || extension == 'png' || extension == "webp") {
            if (typeof(FileReader) != 'undefined') {
                img_holder.empty();
                var reader = new FileReader();
                reader.onload = function(e) {
                    $('<img/>', { 'src': e.target.result, 'class': 'img-fluid', 'style': 'max-width:100px; margin-bottom:10px;' }).appendTo(img_holder);
                }
                img_holder.show();
                reader.readAsDataURL($(this)[0].files[0]);
            } else {
                $(img_holder).html('Este navagador no soporta la extension FileReader');
            }
        } else {
            $(img_holder).empty();
        }
    });

    /// OBTIENE TODOS LOS REGISTROS
    function getDepartamentos(page) {
        $.get('/getDepartamentos', {}, function(data) {
            $('#all-departments').html(data.result);
            $('#pagination-links').html(data.links);
        }, 'json');
    }
    getDepartamentos(1);

    /// OBTIENE LOS REGISTROS BUSCADOS
    $(document).on('keyup', '.search', function() {
        if ($(this).val().length > 0) {
            var search = $(this).val();
            $.get('/getDepartamentos', { search: search }, function(data) {
                $('#all-departments').html(data.result);
                $('#pagination-links').html(data.links)
            }, 'json');
            return;
        }
        getDepartamentos(1);
    });

    /// OBTIENE LOS REGISTROS PAGINADOS
    $(document).on('click', '.page-link', function(event) {
        event.preventDefault();
        var page = $(this).attr('href').split('page=')[1];
        paginarDepartamentos(page);
    });

    function paginarDepartamentos(page) {
        var search = $('.search').val();
        $.get('/getDepartamentos', { page: page, search: search }, function(data) {
            $('#all-departments').html(data.result);
            $('#pagination-links').html(data.links);
        }, 'json');
    }
    /// =================

    /// ELIMINA UN REGISTRO
    $(document).on('click', '.deleteBtn', function() {
        var departamento_id = $(this).data('id');
        Swal.fire({
            title: 'Alerta',
            text: "Estás seguro de borrar el registro",
            icon: 'warning',
            showCancelButton: true,
            confirmButtonColor: '#3085d6',
            cancelButtonColor: '#d33',
            confirmButtonText: 'Sí, Borrarlo!'
        }).then((result) => {
            if (result.isConfirmed) {
                $.ajax({
                    headers: {
                        'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')
                    },
                    url: "/deleteDepartamento",
                    method: "POST",
                    data: { departamento_id: departamento_id },
                    dataType: 'json',
                    success: function(data) {
                        if (data.code == 1) {
                            getDepartamentos();
                            toastr.success(data.msg);
                        } else {
                            toastr.error(data.msg);
                        }
                    }
                });
            }
        })
    });
});